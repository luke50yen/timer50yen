#!/bin/bash
# filepath: /home/andrew/Documents/code-projects/timer50yen/build-packages.sh

set -e  # Exit on any error

# Configuration
PROJECT_NAME="timer50yen"
SPEC_FILE="timer50yen.spec"
BUILD_DIR="build"

# Extract version from existing spec file
VERSION=$(grep "^Version:" ${SPEC_FILE} | awk '{print $2}')
RELEASE=$(grep "^Release:" ${SPEC_FILE} | awk '{print $2}' | cut -d'%' -f1)

echo "Building packages for ${PROJECT_NAME} v${VERSION}-${RELEASE}"

# Clean previous builds
echo "Cleaning previous builds..."
rm -rf ${BUILD_DIR}
rm -f ${PROJECT_NAME}-${VERSION}.tar.gz
rm -f ${PROJECT_NAME}-${VERSION}-${RELEASE}.*.rpm
make clean 2>/dev/null || true

# Create build directory structure for RPM
echo "Creating RPM build directory structure..."
mkdir -p ${BUILD_DIR}/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

# Create source tarball
echo "Creating source tarball..."
tar --exclude='.git' \
    --exclude='build' \
    --exclude='*.rpm' \
    --exclude='*.tar.gz' \
    --exclude=${PROJECT_NAME} \
    -czf ${BUILD_DIR}/SOURCES/${PROJECT_NAME}-${VERSION}.tar.gz \
    --transform "s,^,${PROJECT_NAME}-${VERSION}/," \
    *

# Also create a copy in current directory for distribution
cp ${BUILD_DIR}/SOURCES/${PROJECT_NAME}-${VERSION}.tar.gz .

# Copy spec file to build directory
echo "Using existing spec file..."
cp ${SPEC_FILE} ${BUILD_DIR}/SPECS/

# Build RPM
echo "Building RPM package..."
rpmbuild --define "_topdir $(pwd)/${BUILD_DIR}" \
         -ba ${BUILD_DIR}/SPECS/${SPEC_FILE}

# Copy RPMs to current directory
echo "Copying RPM files..."
find ${BUILD_DIR}/RPMS -name "*.rpm" -exec cp {} . \; 2>/dev/null || echo "No binary RPMs found"
find ${BUILD_DIR}/SRPMS -name "*.rpm" -exec cp {} . \; 2>/dev/null || echo "No source RPMs found"

# Display results
echo ""
echo "Package build complete!"
echo "Generated files:"
ls -la *.tar.gz *.rpm 2>/dev/null || echo "No packages found"

echo ""
echo "Files ready for upload:"
echo "- Source: ${PROJECT_NAME}-${VERSION}.tar.gz"
for rpm in *.rpm 2>/dev/null; do
    if [ -f "$rpm" ]; then
        echo "- RPM: $rpm"
    fi
done
