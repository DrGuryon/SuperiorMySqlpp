#!/bin/sh

if [ ! "$(dpkg -l | grep socat)" ]; then
    echo >&2 "ERROR: Please install socat first:"
    echo >&2 "          apt-get install socat"
    exit 1
fi

set -e
PREFIX="`hostname`-`id -u`-`echo $$`-"
IMAGE_NAME="${PREFIX}superiormysqlpp-test-mysql"
CONTAINER_NAME="${PREFIX}superiormysqlpp-testdb"
docker build --pull -t ${IMAGE_NAME} ../db
docker rm -f ${CONTAINER_NAME} 2>&1 >/dev/null || true
docker run -d -P --name ${CONTAINER_NAME} ${IMAGE_NAME} #1>/dev/null
MYSQL_HOST=`docker inspect --format='{{.NetworkSettings.IPAddress}}' ${CONTAINER_NAME}`
set +e

LOCAL_TMP_SOCKET="/tmp/${CONTAINER_NAME}.sock"

# Create local socket forwarded to docker's 3307 port where is the traffic forwarded to docker mysql socket
socat "UNIX-LISTEN:$LOCAL_TMP_SOCKET,fork,reuseaddr,unlink-early,mode=777" \
    TCP:$MYSQL_HOST:3307 &

./tester ${MYSQL_HOST} 3306 ${CONTAINER_NAME} ${LOCAL_TMP_SOCKET} --reporter=spec
RESULT=$?

echo
echo "To manually test socket forwarding through 3307, try:"
echo "mysql -uroot -ppassword -h $MYSQL_HOST -P 3307"
echo "mysql -uroot -ppassword --socket $LOCAL_TMP_SOCKET"

echo
read -p "Press Enter to continue .. (this will kill running docker & socat forwarding)" _
echo

# Remove local socket forwarding (so kill last job put to background)
kill $!

echo "Removing temporary created docker container .."
docker rm -f ${CONTAINER_NAME}

if [ ! "$?" -eq "0" ]; then
    echo >&2 "Removing docker container '${CONTAINER_NAME}' failed"
fi

exit ${RESULT}
