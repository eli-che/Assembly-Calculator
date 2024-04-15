#!/bin/bash

FILENAME="$1"
PROLOGUE="src/Prologue.s"
EPILOGUE="src/Epilogue.s"
CALC3I="bin/calc3i.exe"

USAGE(){
  echo "Run: ./x86-64-driver.sh <test/filename.calc>"
  echo "Assembly file created in root directory, Executable created in outputexe folder"
}

FILE="$(basename -- $FILENAME)"
base="${FILE%.*}"
src="src/fact.s"

if [[ ${FILENAME: -5} != ".calc" ]]; then
    echo "Invalid format!"
		USAGE
		exit 1
fi

if [[ ! -f ${FILENAME} ]]; then
    echo "${FILENAME} error, file not found"
    USAGE
    exit 1
fi



#fill base file with prologue and epilogue
cat $PROLOGUE > $base.s
$CALC3I < $FILENAME >> $base.s
cat $EPILOGUE >> $base.s
if [[ "$base" == "fact" ]]; then
  gcc $base.s $src -o outputexe/$base lib/lib.a
else
  gcc $base.s -o outputexe/$base lib/lib.a
fi
