// TestFormattedInteger.java
public class TestFormattedInteger {
    public static void main(String[] args) {
        // Criar instâncias dos três tipos
        FormattedInteger decimal = new PlainFormattedInteger();
        FormattedInteger hex = new HexFormattedInteger();
        FormattedInteger octal = new OctalFormattedInteger();
        
        // Teste 1: Número decimal negativo (-211)
        System.out.println("\nTeste 1: Número -211");
        decimal.setString("-211");
        int value = decimal.getInt();
        hex.setInt(value);
        octal.setInt(value);
        showAllFormats(decimal, hex, octal);
        
        // Teste 2: Número hexadecimal (0xFF)
        System.out.println("\nTeste 2: Número 0xFF");
        String result = hex.setString("0xFF");
        if (!result.isEmpty()) {
            System.out.println("Erro ao definir hex: " + result);
        } else {
            value = hex.getInt();
            decimal.setInt(value);
            octal.setInt(value);
            showAllFormats(decimal, hex, octal);
        }
        
        // Teste 3: Número octal (0777)
        System.out.println("\nTeste 3: Número 0777");
        result = octal.setString("0777");
        if (!result.isEmpty()) {
            System.out.println("Erro ao definir octal: " + result);
        } else {
            value = octal.getInt();
            decimal.setInt(value);
            hex.setInt(value);
            showAllFormats(decimal, hex, octal);
        }
        
        // Teste 4: Erros de formato
        System.out.println("\nTeste 4: Testando erros de formato");
        testError(decimal, "abc", "decimal");
        testError(hex, "FF", "hexadecimal");
        testError(octal, "789", "octal");
    }
    
    private static void showAllFormats(FormattedInteger decimal, FormattedInteger hex, 
                                     FormattedInteger octal) {
        System.out.println("Decimal: " + decimal.getString());
        System.out.println("Hexadecimal: " + hex.getString());
        System.out.println("Octal: " + octal.getString());
    }
    
    private static void testError(FormattedInteger num, String invalidInput, String type) {
        System.out.println("\nTestando entrada inválida para " + type + ": " + invalidInput);
        String error = num.setString(invalidInput);
        System.out.println("Mensagem de erro: " + error);
    }
}
