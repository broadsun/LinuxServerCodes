#a=$( expr 'helloworld20140501.txt' : '.*\([0-9]\{8\}\).*' )
dirname=$1
for filename in $(ls $dirname)
do
    destname=$( expr "$filename" : '[0-9]*-[0-9]*\(.*\)' )
    mv $dirname/$filename $dirname/$destname
done
