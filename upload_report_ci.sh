#!/bin/bash

# Upload to Report.CI
python upload_report_ci.py --include='*.xml' --framework=gtest
