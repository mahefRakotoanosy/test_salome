#! /bin/bash
# This test launches in parallel a great number of instances of a usual use case
WORKDIR=`mktemp -d`
echo WORKDIR: $WORKDIR
cat > $WORKDIR/command.sh <<< 'echo "OK" > result.txt'
chmod 755 $WORKDIR/command.sh
pid_launcher=''
for i in {1..500}
do
  python launcher_use_case.py $WORKDIR 2> $WORKDIR/log$i.err &
  pid_launcher=$pid_launcher" "$!
done
exit_code=0
for i in "$pid_launcher"
do
  wait $i
  ret=$?
  if [ $ret -ne "0" ]
  then
     echo "Error detected!"
     exit_code=1
  fi
done
# list of error files not empty
ls -l $WORKDIR/*.err | awk '{if ($5 != "0") print $0}'
exit $exit_code