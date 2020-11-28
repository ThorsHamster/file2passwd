#!/usr/bin/env python

import os
import sys
import argparse
import subprocess
import re
import fnmatch
import urllib
import json

if sys.version_info >= (3, 0):
    import urllib

    from urllib.parse import urlencode
    from urllib.request import Request, urlopen


else:
    from urllib import urlencode
    import urllib2
    from urllib2 import Request, urlopen

env = os.environ


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


parser = argparse.ArgumentParser()

parser.add_argument("-i", "--include", nargs='+',
                    help="Files to include, can cointain unix-style wildcard. (default *.xml)",
                    default=["*.xml", "*.json", "*.trx", "*.tap"])
parser.add_argument("-x", "--exclude", nargs='+', help="Files to exclude, can cointain unix-style wildcard.",
                    default=[])
parser.add_argument("-l", "--file_list", nargs='+',
                    help="Explicit file list, if given include and exclude are ignored.", default=None)

parser.add_argument("-t", "--token",
                    help="Token to authenticate (not needed for public projects on appveyor, travis and circle-ci")
parser.add_argument("-n", "--name",
                    help="Custom defined name of the upload when commiting several builds with the same ci system")
parser.add_argument("-f", "--framework",
                    choices=["boost", "junit", "testng", "xunit", "cmocka", "unity", "criterion", "bandit",
                             "catch", "cpputest", "cute", "cxxtest", "gtest", "qtest", "go", "testunit", "rspec",
                             "minitest",
                             "nunit", "mstest", "xunitnet", "phpunit", "pytest", "pyunit", "mocha", "ava", "tap",
                             "tape", "qunit", "doctest", "nunit"],
                    help="The used unit test framework - if not provided the script will try to determine it")
parser.add_argument("-r", "--root_dir",
                    help="The root directory of the git-project, to be used for aligning paths properly. Default is the git-root.")
parser.add_argument("-s", "--ci_system", help="Set the CI System manually. Should not be needed")
parser.add_argument("-b", "--build_id",
                    help="The identifer The Identifer for the build. When used on a CI system this will be automatically generated.")
parser.add_argument("-a", "--sha", help="Specify the commit sha - normally determined by invoking git")
parser.add_argument("-c", "--check_run", help="The check-run id used by github, used to update reports.")
parser.add_argument("-d", "--id_file", help="The file to hold the check id given by github.",
                    default=".report-ci-id.json")
parser.add_argument("-D", "--define", help="Define a preprocessor token for the name lookup.", nargs='+')
parser.add_argument("-p", "--preset", help="Select a definition & include preset from .report-ci.yaml.")
parser.add_argument("-m", "--merge", help="Merge similar annotations from different check-runs.")

args = parser.parse_args()

if not args.check_run:
    try:
        args.check_run = json.loads(open(args.id_file, "r").read())["github"]
    except:
        pass

## Alright, now detect the CI - thanks to codecov for the content

root_dir = None
branch = None
service = None
pr = None
commit = None
build = None
build_url = None
search_in = None
slug = None
run_name = args.name
build_id = None
account_name = None
root_dir = None
os_name = None

if env.get("GITHUB_ACTIONS") == "true":
    print(bcolors.HEADER + "    Github actions CI detected." + bcolors.ENDC)
    # https://help.github.com/en/actions/configuring-and-managing-workflows/using-environment-variables
    service = "github-actions"

    build_id = env.get("GITHUB_RUN_ID")
    commit = env.get("GITHUB_SHA")
    slug = env.get("GITHUB_REPOSITORY")
    account_name = env.get("GITHUB_ACTOR")
    root_dir = env.get("GITHUB_WORKSPACE")
    branch = env.get("GITHUB_REF")
    if branch:
        branch = os.path.basename(branch)

else:
    print(bcolors.HEADER + "    No CI detected." + bcolors.ENDC)

if args.root_dir:
    root_dir = args.root_dir

if args.sha:
    commit = args.sha
if not commit:
    commit = subprocess.check_output(["git", "rev-parse", "HEAD"]).decode().replace('\n', '')

print(bcolors.OKBLUE + "    Commit hash: " + commit + bcolors.ENDC)

if not root_dir:
    root_dir = subprocess.check_output(["git", "rev-parse", "--show-toplevel"]).decode().replace('\n', '')

print(bcolors.OKBLUE + "    Root dir: " + root_dir + bcolors.ENDC)

owner, repo = None, None
if slug:
    try:
        (owner, repo) = slug.split('/')
    except:
        print(bcolors.WARNING + "Invalid Slug: '{0}'".format(slug) + bcolors.ENDC)

if not owner or not repo:
    remote_v = subprocess.check_output(["git", "remote", "-v"]).decode()
    match = re.search(r"(?:https://|ssh://git@)github.com/([-_A-Za-z0-9]+)/((?:(?!\.git(?:\s|$))[-._A-Za-z0-9])+)",
                      remote_v)
    if match:
        owner = match.group(1)
        repo = match.group(2)
    else:
        match = re.search(r"git@github\.com:([-_A-Za-z0-9]+)/((?:(?!\.git(?:\s|$))[-._A-Za-z0-9])+)", remote_v)
        owner = match.group(1)
        repo = match.group(2)

print(bcolors.OKBLUE + "    Project: " + owner + '/' + repo + bcolors.ENDC)


# find
def match_file(file_abs):
    match = False
    file = os.path.relpath(file_abs)
    for inc in args.include:
        if fnmatch.fnmatch(file, inc) or fnmatch.fnmatch(file_abs, inc):
            match = True
            break

    for exc in args.exclude:
        if fnmatch.fnmatch(file, exc) or fnmatch.fnmatch(file_abs, exc):
            match = False
            break

    return match


boost_test = []
junit_test = []
xunit_test = []
testng_test = []
criterion_test = []
complete_content = []
file_list = []
bandit = []
catch_test = []
cxxtest = []
qtest = []
go_test = []
testunit = []
rspec = []
phpunit = 0
pytest = 0
mocha = []

tap_test = []
ava = 0

mstest = []
xunitnet = []
nunit = []
doctest = []

if not args.file_list:
    for wk in os.walk(root_dir):
        (path, subfolders, files) = wk
        if fnmatch.fnmatch(path, "*/.git*"):
            continue
        for file in files:
            abs_file = os.path.join(path, file)
            file_list.append(abs_file)
else:
    for file in args.file_list:
        abs = os.path.abspath(file)
        if not os.path.isfile(abs):
            print(bcolors.FAIL + "Could not find file '" + file + "'" + bcolors.ENDC)
            exit(1)
        else:
            file_list.append(abs)

for abs_file in file_list:
    if match_file(abs_file):
        content = None

        ext = os.path.splitext(abs_file)[1].lower()
        binary_content = open(abs_file, "rb").read()
        try:
            content = binary_content.decode('ascii')
        except UnicodeDecodeError:
            try:
                content = binary_content.decode('utf-8').encode("ascii", "ignore").decode('ascii')
            except UnicodeDecodeError:
                try:
                    content = binary_content.decode('utf-16').encode("ascii", "ignore").decode('ascii')
                except UnicodeDecodeError:
                    print(
                        bcolors.FAIL + "Can't figure out encoding of file " + abs_file + ", ignoring it" + bcolors.ENDC)
                    continue

        complete_content.append(content)

        if ext == ".xml":
            if re.match(r"(<\?[^?]*\?>\s*)?<(?:TestResult|TestLog)>\s*<TestSuite", content):
                print("    Found " + abs_file + " looks like boost.test")
                boost_test.append(content)
                continue

            if re.match(r"(<\?[^?]*\?>\s*)?<TestCase", content) and (
                    content.find("<QtVersion>") != -1 or content.find("<qtversion>") != -1):
                print("    Found " + abs_file + ", looks like qtest")
                qtest.append(content)
                continue

            if re.match(
                    r'(<\?[^?]*\?>\s*)?<!-- Tests compiled with Criterion v[0-9.]+ -->\s*<testsuites name="Criterion Tests"',
                    content):
                print("    Found " + abs_file + ", looks like criterion")
                criterion_test.append(content)
                continue

            if re.match(r"(<\?[^?]*\?>\s*)?(<testsuites>\s*)?<testsuite[^>]", content):  # xUnit thingy
                if content.find('"java.version"') != -1 and (
                        content.find('org.junit') != -1 or content.find('org/junit') != -1 or content.find(
                        'org\\junit') != -1):
                    print("    Found " + abs_file + ", looks like JUnit")
                    junit_test.append(content)
                elif content.find('"java.version"') != -1 and (
                        content.find('org.testng') != -1 or content.find('org/testng') != -1 or content.find(
                        'org\    estng') != -1):
                    print("    Found " + abs_file + ", looks like TestNG")
                    testng_test.append(content)
                elif content.find('"java.version"') == -1 and content.find('<testsuite name="bandit" tests="') != -1:
                    print("    Found " + abs_file + ", looks like Bandit")
                    bandit.append(content)
                elif content.find('.php') != -1:
                    print("    Found " + abs_file + ", looks like PHPUnit")
                    phpunit += 1
                    xunit_test.append(content)
                elif content.find('.py') != -1:
                    print("    Found " + abs_file + ", looks like PyTest")
                    pytest += 1
                    xunit_test.append(content)
                else:
                    print("    Found " + abs_file + ", looks like some xUnit")
                    xunit_test.append(content)
                continue

            if re.match(r'(<\?[^?]*\?>\s*)?<Catch\s+name=', content):
                print("    Found " + abs_file + ", looks like catch")
                catch_test.append(content)
                continue
            if re.match(r'(<\?[^?]*\?>\s*)?<stream>\s*<ready-test-suite>', content):
                print("    Found " + abs_file + ", looks like TestUnit")
                testunit.append(content)
                continue
            if re.match(
                    r'(<\?[^?]*\?>\s*)?(<!--This file represents the results of running a test suite-->)?<test-results\s+name',
                    content) or \
                    re.match(r'(<\?[^?]*\?>\s*)?<test-run id="2"', content):
                print("    Found " + abs_file + ", looks like NUnit")
                nunit.append(content)
                continue
            if re.match(r'(<\?[^?]*\?>)?\s*<assemblies', content):
                print("    Found " + abs_file + ", looks like xUnit.net")
                xunitnet.append(content)
                continue

            if re.match(r'(<\?[^?]*\?>)?\s*<doctest', content):
                print("    Found " + abs_file + ", looks like doctest")
                doctest.append(content)
                continue


        elif ext == ".json" and re.match(r"\s*({|\[)", content):  # Might be JSON, let's see if it fits go
            try:
                lines = content.splitlines()
                json_lines = [json.loads(ln) for ln in lines]
                if all(val in json_lines[0] for val in ["Time", "Action", "Package"]):  # assumption
                    print("Found " + abs_file + ", looks like GoTest")
                    go_test = go_test + [json.loads(ln) for ln in lines]
                    continue
            except:
                pass
            try:
                data = json.loads(content)

                if "version" in data and "examples" in data and "summary" in data and "summary_line" in data:
                    print("Found " + abs_file + ", looks like RSpec")
                    rspec.append(data)
                    continue
                if "stats" in data and "tests" in data and "pending" in data and "passes" in data and "failures" in data:
                    print("Found " + abs_file + ", looks like Mocha")
                    mocha.append(data)
                    continue

            except:
                pass

            # data = loadJson(content)
        elif ext == ".trx" and re.match(r"(<\?[^?]*\?>\s*)?<TestRun", content):
            print("Found " + abs_file + ", looks like MsTest")
            mstest.append((abs_file, content))

        elif ext == ".tap" and re.match(r"TAP version \d+", content):  # is Test anything protocol
            if re.match(r"ava[\\\/]cli.js", content):
                print("Found " + abs_file + ", looks like AVA")
                ava += 1
            else:
                print("Found " + abs_file + ", looks like TAP")
            tap_test.append(content)

upload_content = ""
content_type = ""

if not args.framework:
    # check for different test frameworks

    if len(testng_test) > 0:
        framework = "testng"
        print(bcolors.HEADER + "TestNG detected" + bcolors.ENDC)

    elif len(junit_test) > 0:
        framework = "junit"
        print(bcolors.HEADER + "JUnit detected" + bcolors.ENDC)

    elif len(bandit) > 0:
        framework = "bandit"
        print(bcolors.HEADER + "Bandit detected" + bcolors.ENDC)

    elif phpunit > 0:
        framework = "phpunit"
        print(bcolors.HEADER + "PHPUnit detected" + bcolors.ENDC)

    elif pytest > 0:
        framework = "pytest"
        print(bcolors.HEADER + "PyTest detected" + bcolors.ENDC)

    elif len(xunit_test) > 0:
        framework = "xunit"
        print(bcolors.HEADER + "Unspecified xUnit detected" + bcolors.ENDC)

    elif len(boost_test) > 0:
        framework = "boost"
        print(bcolors.HEADER + "Boost.test detected" + bcolors.ENDC)

    elif len(criterion_test) > 0:
        framework = "criterion"
        print(bcolors.HEADER + "Criterion detected" + bcolors.ENDC)

    elif len(catch_test) > 0:
        framework = "catch"
        print(bcolors.HEADER + "Catch detected" + bcolors.ENDC)

    elif len(cxxtest) > 0:
        framework = "cxxtest"
        print(bcolors.HEADER + "CxxTest detected" + bcolors.ENDC)

    elif len(qtest) > 0:
        framework = "qtest"
        print(bcolors.HEADER + "QTest detected" + bcolors.ENDC)

    elif len(go_test) > 0:
        framework = "go-test"
        print(bcolors.HEADER + "Go detected" + bcolors.ENDC)

    elif len(testunit) > 0:
        framework = "testunit"
        print(bcolors.HEADER + "TestUnit detected" + bcolors.ENDC)

    elif len(mstest) > 0:
        framework = "mstest"
        print(bcolors.HEADER + "MSTest detected" + bcolors.ENDC)

    elif len(nunit) > 0:
        framework = "nunit"
        print(bcolors.HEADER + "NUnit detected" + bcolors.ENDC)

    elif len(xunitnet) > 0:
        framework = "xunitnet"
        print(bcolors.HEADER + "XUnit.net detected" + bcolors.ENDC)

    elif len(rspec) > 0:
        framework = "rspec"
        print(bcolors.HEADER + "RSpec detected" + bcolors.ENDC)

    elif len(mocha) > 0:
        framework = "mocha"
        print(bcolors.HEADER + "Mocha detected" + bcolors.ENDC)

    elif ava > 0:
        framework = "ava"
        print(bcolors.HEADER + "AVA detected" + bcolors.ENDC)

    elif len(tap_test) > 0:
        framework = "tap"
        print(bcolors.HEADER + "Unspecificed TAP detected" + bcolors.ENDC)

    elif len(doctest) > 0:
        framework = "doctest"
        print(bcolors.HEADER + "Doctest detected" + bcolors.ENDC)

    else:

        print(bcolors.FAIL + "No framework selected and not detected." + bcolors.ENDC)
        exit(1)
else:
    framework = args.framework
    print(bcolors.HEADER + framework + " selected" + bcolors.ENDC)

if (framework == "testng"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(testng_test) + "</root>"
    if not run_name: run_name = "TestNG";
elif (framework == "junit"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "".join(junit_test) + "".join(
        ["\n    <file>{0}</file>".format(file) for file in file_list]) + "</root>";
    if not run_name: run_name = "JUnit"
elif framework == "bandit":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(bandit) + "</root>"
    if not run_name: run_name = "Bandit"
elif (framework == "xunit"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "".join(junit_test) + "".join(
        ["\n    <file>{0}</file>".format(file) for file in file_list]) + "</root>";
    if not run_name: run_name = "xUnit"
elif (framework == "boost"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(boost_test) + "</root>"
    if not run_name: run_name = "boost.test"
elif (framework == "cmocka"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "CMocka"
elif (framework == "criterion"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(criterion_test) + "</root>"
    if not run_name: run_name = "Criterion"
elif (framework == "catch"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(catch_test) + "</root>"
    if not run_name: run_name = "Catch"
elif (framework == "unity"):
    content_type = "text/plain"
    upload_content = "\n".join(complete_content)
    if not run_name: run_name = "Unity"
elif (framework == "cpputest"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "CppUTest"
elif (framework == "minitest"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "Minitest"
elif (framework == "cute"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "Cute"
elif (framework == "doctest"):
    content_type = "text/xml"
    upload_content = "<root>" + "".join(doctest) + "</root>"
    if not run_name: run_name = "Doctest"
elif framework == "cxxtest":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(cxxtest) + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "CxxTest"
elif framework == "gtest":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "GoogleTest"
elif framework == "qtest":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(qtest) + "</root>"
    if not run_name: run_name = "QTest"
elif framework == "testunit":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(testunit) + "</root>"
    if not run_name: run_name = "TestUnit"
elif framework == "rspec":
    content_type = "application/json"
    upload_content = json.dumps(rspec)
    if not run_name: run_name = "RSpec"
elif framework == "mocha":
    content_type = "application/json"
    upload_content = json.dumps(mocha)
    if not run_name: run_name = "Mocha"
elif framework == "xunitnet":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunitnet) + "</root>"
    if not run_name: run_name = "XUnit.Net"
elif framework == "nunit":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(nunit) + "</root>"
    if not run_name: run_name = "NUnit"
elif framework == "phpunit":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "PHPUnit"
elif framework == "pytest":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "PyTest"
elif framework == "pyunit":
    content_type = "text/xml"
    upload_content = "<root>" + "".join(xunit_test) + "</root>"
    if not run_name: run_name = "PyUnit"
elif (framework == "ava"):
    content_type = "text/plain"
    upload_content = "\n".join(tap_test)
    if not run_name: run_name = "Ava"
elif (framework == "qunit"):
    content_type = "text/plain"
    upload_content = "\n".join(tap_test)
    if not run_name: run_name = "QUnit"
elif (framework == "tap"):
    content_type = "text/plain"
    upload_content = "\n".join(tap_test)
    if not run_name: run_name = "Tap"
elif (framework == "tape"):
    content_type = "text/plain"
    upload_content = "\n".join(tap_test)
    if not run_name: run_name = "Tape"

elif framework == "mstest":
    content_type = "text/xml"

    filename = "",
    time = None
    for (fn, content) in mstest:
        time_ = os.path.getmtime(fn)
        if time == None or time_ > time:
            filename = fn
            upload_content = content
            time_ = time

    print(bcolors.HEADER + "MSTest picked " + filename + bcolors.ENDC)
    if not run_name: run_name = "MSTest";

elif framework == "go-test":
    content_type = "application/json"
    upload_content = json.dumps({'files': file_list, 'test_data': go_test})
    if not run_name: run_name = "Go";

upload_content = upload_content.strip()
if len(upload_content) == 0:
    print(bcolors.FAIL + " No test data to upload.")
    exit(1)

if service and not args.name and run_name:
    if os_name:
        run_name += " [" + service + ", " + os_name + "]"
    else:
        run_name += " [" + service + "]"

headers = {}

query = {
    'framework': framework,
    'owner': owner,
    'repo': repo,
    'head-sha': commit,
    'root-dir': root_dir,
    'branch': branch,
    'account-name': account_name,
}

if run_name: query['run-name'] = run_name
if args.check_run: query['check-run-id'] = args.check_run
if args.preset: query['preset'] = args.preset
if args.define: query['define'] = args.define
if args.merge: query["merge"] = args.merge

url = "https://api.report.ci/publish/"

if sys.version_info >= (3, 0):
    url = urllib.request.urlopen(url).geturl()
else:
    url = urllib.urlopen(url).geturl()

if service and service in ["travis-ci", "appveyor", "circle-ci", "github-actions"] and args.token == None:
    query["build-id"] = build_id
    url += service + "/"

if sys.version_info >= (3, 0):
    upload_content = bytes(upload_content, "utf8")

if args.check_run and not args.name and 'run-name' in query:
    del query['run-name']

request = Request(url + "?" + urlencode(query), upload_content, headers)
if args.token:   request.add_header("Authorization", "Bearer " + args.token)
if content_type: request.add_header("Content-Type", content_type)

if args.check_run:
    request.get_method = lambda: 'PATCH'

try:
    response = urlopen(request).read().decode()
    print(bcolors.OKGREEN + "Published: '{0}".format(response) + bcolors.ENDC)
    res = json.loads(response)
    ch_id = str(res["id"])
    print('Uploaded check_run https://report.ci/reports/gh/{}/{}/rep/{}'.format(owner, repo, ch_id))
    open(args.id_file, 'w').write(response)
    exit(0)

except Exception as e:
    print(bcolors.FAIL + 'Publishing failed: {0}'.format(e) + bcolors.ENDC)
    try:
        print(e.read())
    except:
        exit(1)
    exit(1)
