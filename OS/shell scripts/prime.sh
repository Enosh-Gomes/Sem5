echo "Enter a number: "
read num

if [ $num -le 1 ]; then 
	echo "$num is not a prime number."
	exit
fi

is_prime=1
i=2

while [ $((i*i)) -le $num ]
do
	if [ $((num % i)) -eq 0 ];
	then is_prime=0
	break
	fi
	i=$((i+1))
done

if [ $is_prime -eq 0 ]
then
	echo "$num is not a prime number."
else
	echo "$num is a prime number."
fi
