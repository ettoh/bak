#!/bin/bash 

main(){
    # correct amount of arguments?
    if [ "$#" -ne 1 ]; then
        echo "Usage: bak <filename>"
        return 1
    fi

    # does the given file exist?
    if [ ! -f $1 ]; then
        echo "Incorrect file given! Make sure the file exists."
        return 1
    fi

    # split filepath into directory and filename
    dir=$(dirname "$1")
    filename=$(basename "$1")

    # find the latest backup id
    latest_id=$(find "$dir" -type f -maxdepth 1 -name "$filename*" -exec echo '{}' + | \
        grep -Eo '[0-9]+[.]bak' | sort | tail -1 | grep -Eo '[0-9]+')

    # is this the first backup?
    if [ -z "$latest_id" ]; then
        latest_id="-1" # later, +1 will yield 0
    fi

    # create backup
    new_id=$(($latest_id + 1))
    new_filename=$(printf '%s-%02d.bak' $1 $new_id)
    cp -i "$1" "$new_filename"
    echo "The file $1 has been backed up as $new_filename."
}

main "$@"
