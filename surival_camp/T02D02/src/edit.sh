if [ $# -ne 3 ]; then
    echo "incorrecr count of arguments"
    exit 1
fi

F_PATH=$1
OLD_STR=$2
NEW_STR=$3
LOG_FILE="src/files.log"

if [ ! -f "$F_PATH" ]; then
    echo "file not exist"
    exit 1
fi
if [ ! -r "$F_PATH" ] || [ ! -w "$F_PATH" ]; then
    echo "can't read/write"
    exit 1
fi

OLD_FILE="~$(basename "$F_PATH")"
cp "$F_PATH" "$OLD_FILE"

sed -i "" "s|$OLD_STR|$NEW_STR|g" "$F_PATH"

if cmp -s "$F_PATH" "$OLD_FILE"; then
    echo "nothing change"
    rm "$OLD_FILE"
    exit 0
fi

SIZE=$(wc -c < "$F_PATH")
DATE=$(date +"%Y-%m-%d %H:%M")
HASH=$(sha256sum "$F_PATH" | awk '{print $1}')
TYPE="sha256"

LOG_STR="$F_PATH - $SIZE - $DATE - $HASH - $TYPE"
echo $LOG_STR >> $LOG_FILE

rm "$OLD_FILE"
echo "DONE"
