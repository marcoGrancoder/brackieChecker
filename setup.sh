SOURCE="main.cpp"
BINARY="balanced"
INSTALL_DIR="/usr/bin"

#check for g++
if type g++ &> /dev/null; then
    echo "g++ installed"
else
    echo "g++ not installed"
    exit 1
fi 
#check if SOURCE exists
if [ ! -f "$SOURCE" ]; then
    echo "Error: Balance Checker Source not found"
    exit 1
fi
#compile source code
echo "Compiling... "
g++ "$SOURCE" -o "$BINARY" 

if [ ! -f "$BINARY" ]; then
    echo "Error: Failed to compile"
    exit 1
fi

#move the binary to /usr/local/bin
echo "Installing to $INSTALL_DIR"
mv "$BINARY" "$INSTALL_DIR/"

# confirm installation 
if [ -f "$INSTALL_DIR/$BINARY" ]; then
    echo "Installation successful"
else
    echo "Installation unsuccessful"
fi