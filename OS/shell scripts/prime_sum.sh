echo -n "Prime numbers from 1 to 50 are: "

sum=0
num=2

while [ $num -le 50 ]
do
	is_prime=1
	i=2
	while [ $((i*i)) -le $num ]
	do
		if [ $((num % i)) -eq 0 ]
		then is_prime=0
		break
		fi
		i=$((i+1))
	done
	
	if [ $is_prime -eq 1 ]; then
	echo -n "$num, "
	sum=$((sum+num))
	fi

	num=$((num+1))
done

echo
echo "Sum of prime numbers from 1 to 50 is: $sum"
