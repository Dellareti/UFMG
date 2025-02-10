public class Main {
    public static void main(String[] args) {
        // Exemplo de uso
        FormattedInteger decimal = new PlainFormattedInteger();
        FormattedInteger hex = new HexFormattedInteger();
        FormattedInteger octal = new OctalFormattedInteger();
        
        // Teste com o número -211
        decimal.setString("-211");
        hex.setInt(decimal.getInt());
        octal.setInt(decimal.getInt());
        
        System.out.println("Decimal: " + decimal.getString());
        System.out.println("Hex: " + hex.getString());
        System.out.println("Octal: " + octal.getString());
    }
}
