public class Int {
    private int value;

    // Construtor
    public Int(int value) {
        this.value = value;
    }

    // toString
    @Override
    public String toString() {
        return String.valueOf(value);
    }

    // Operações matemáticas
    public Int plus(Int other) {
        return new Int(this.value + other.value);
    }

    public Int minus(Int other) {
        return new Int(this.value - other.value);
    }

    public Int times(Int other) {
        return new Int(this.value * other.value);
    }

    public Int div(Int other) {
        if (other.value == 0) throw new ArithmeticException("Division by zero");
        return new Int(this.value / other.value);
    }

    // Verificação de primo
    public boolean isPrime() {
        if (value < 2) return false;
        for (int i = 2; i <= Math.sqrt(value); i++) {
            if (value % i == 0) return false;
        }
        return true;
    }
}
