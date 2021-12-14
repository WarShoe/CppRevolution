export TOP_DIR=$PWD
export BUILD_DIR=$TOP_DIR/build
export CSHARP_DIR=$TOP_DIR/csharp/tests

function show_info() {
    echo 'DOTNET!!!!!!!!!!!!!'
    dotnet --version
    echo 'Ubuntu'
    lsb_release –a
    
    echo '--- CUT HERE begin ---'
    mkdir proj
    cd proj
    dotnet new nunit
    cat proj.csproj
    echo '--- CUT HERE end ---'
}

function install_dotnet() {
    #https://docs.microsoft.com/en-us/dotnet/core/install/linux-ubuntu

    apt install -y gpg
    wget -O - https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor -o microsoft.asc.gpg
    mv microsoft.asc.gpg /etc/apt/trusted.gpg.d/
    wget https://packages.microsoft.com/config/ubuntu/20.10/prod.list
    mv prod.list /etc/apt/sources.list.d/microsoft-prod.list
    chown root:root /etc/apt/trusted.gpg.d/microsoft.asc.gpg
    chown root:root /etc/apt/sources.list.d/microsoft-prod.list
    apt update
    apt install -y apt-transport-https
    apt update
    apt install -y dotnet-sdk-6.0

#    dpkg --purge packages-microsoft-prod && dpkg -i packages-microsoft-prod.deb
#    apt update
#    apt install -y apt-transport-https 
#    apt install -y dotnet-sdk-6.0
}

function install_packages() {
    apt install -y meson libfmt-dev python python-pybind11 
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
    dotnet test -l "console;verbosity=detailed"
}

function publish_cpp_to_csharp() {
    # FIXME: get dotnet build directory automatically
    #export p=$CSHARP_DIR/bin/Debug/net5.0
    export p=$CSHARP_DIR/bin/Debug/netcoreapp3.1
    mkdir -p $p
    cp -a $BUILD_DIR/csharp/* $p
}


#show_info
install_packages
cleanup_all
build_cpp
publish_cpp_to_csharp
build_csharp
test_csharp
