key=$((RANDOM%99999999+10000000))

wget -O - --method=POST http://localhost:8080/device --body-data="id=$1&n=$2&k=${key}"
