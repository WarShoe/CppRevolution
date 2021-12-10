export TOP_DIR=$PWD
export BUILD_DIR=$TOP_DIR/build
export CSHARP_DIR=$TOP_DIR/csharp/tests

function install_packages() {
    apt install -y meson libfmt-dev python3 python-pybind11 
}

function cleanup_all() {
    rm -rf $BUILD_DIR
    rm -rf $CSHARP_DIR/bin
}

function build_cpp() {
    meson $BUILD_DIR
    cd $BUILD_DIR
    ninja
}

function build_csharp() {
    cd $CSHARP_DIR
    dotnet build
}

function test_csharp() {
    cd $CSHARP_DIR
    dotnet test
}

function publish_cpp_to_csharp() {
    mkdir -p $CSHARP_DIR/bin/Debug/net5.0
    cp -a $BUILD_DIR/csharp/* $CSHARP_DIR/bin/Debug/net5.0
}

install_packages
cleanup_all
build_cpp
publish_cpp_to_csharp
build_csharp
test_csharp
