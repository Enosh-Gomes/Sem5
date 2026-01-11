echo "Enter first number: "
read a

echo "Enter second number: "
read b

echo "Results of floating-point arithmetic operations:"
echo 
echo "Addition       : $(echo "scale=2; $a + $b" | bc)"
echo "Subtraction    : $(echo "scale=2; $a - $b" | bc)"
echo "Multiplication : $(echo "scale=2; $a * $b" | bc)"
echo "Division       : $(echo "scale=2; $a / $b" | bc)"
