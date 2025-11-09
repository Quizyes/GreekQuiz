#!/bin/bash

# Define the directory containing the files
DIRECTORY="./src"

# Define the text to prepend
PREPEND_TEXT="\
////////////////////////////////////////////////////////////////////////// \n\
//                                                                      // \n\
// Greek Quiz - a suite of apps for practicing Ancient Greek.           // \n\
//                                                                      // \n\
// Copyright 2025, Greg Recco                                           // \n\
//                                                                      // \n\
// Greek Quiz is released under the GNU General Public Licence v3       // \n\
// or later (GPL-3.0-or-later). The license is found in the 'LICENSE'   // \n\
// file in the root of this repository, or at                           // \n\
// https://www.gnu.org/licenses/gpl-3.0.en.html                         // \n\
//                                                                      // \n\
// The source code repository for Greek Quiz is available at            // \n\
// https://github.com/Quizyes/GreekQuiz                                 // \n\
//                                                                      // \n\
////////////////////////////////////////////////////////////////////////// \n\
"

# Loop through all files in the specified directory
for FILE in "$DIRECTORY"/*; do
  # Check if it's a regular file (not a directory)
  if [ -f "$FILE" ]; then
    # Create a temporary file
    TEMP_FILE=$(mktemp) 

    # Prepend the text to the temporary file
    echo -e "$PREPEND_TEXT" > "$TEMP_FILE" 

    # Append the original file's content to the temporary file
    cat "$FILE" >> "$TEMP_FILE" 

    # Replace the original file with the modified temporary file
    mv "$TEMP_FILE" "$FILE" 

    echo "Prepended text to: $FILE"
  fi
done
