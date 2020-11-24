#!/bin/bash

# Upload to Report.CI
python report_ci_upload.py --include='*.xml' --framework=gtest
