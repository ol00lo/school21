if [ $# -ne 1 ]; then
    echo "incorrecr count of arguments"
    exit 1
fi

LOG_FILE=$1

if [ ! -f "$LOG_FILE" ] || [ ! -r "$LOG_FILE" ]; then
    echo "file not exist or can't readed"
    exit 1
fi
if [ ! -s "$LOG_FILE" ]; then
    echo "0 0 0"
    exit 0
fi

N_STRINGS=$(wc -l < "$LOG_FILE")
ALL_NAMES=$(cut -d'-' -f1 "$LOG_FILE")
UNIQUE_NAMES=$(echo "$ALL_NAMES" | sort -u)
COUNT_UNIQUE_NAMES=$(echo "$UNIQUE_NAMES" | wc -l)

TOTAL_COUNT=0
for CURRENT_NAME in $UNIQUE_NAMES; do
    HASHES_FOR_NAME=$(grep $CURRENT_NAME $LOG_FILE |cut -d'-' -f6)
    COUNT=$(echo "$HASHES_FOR_NAME" | sort -u | wc -l)
    if [ $COUNT -gt 1 ]; then
        TOTAL_COUNT=$((TOTAL_COUNT+COUNT-1))
    fi
done

echo ""$N_STRINGS" "$COUNT_UNIQUE_NAMES" "$TOTAL_COUNT""
