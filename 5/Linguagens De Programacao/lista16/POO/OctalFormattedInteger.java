public class OctalFormattedInteger extends AbstractFormattedInteger {
    @Override
    public String getString() {
        return "0" + Integer.toOctalString(value);
    }
    
    @Override
    public String setString(String s) {
        if (s.charAt(0) != '0') {
            return "Octal requires a leading zero.";
        }
        
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!('0' <= c && c <= '7')) {
                return "Octal digits must be 0..7";
            }
        }
        
        value = (int) Long.parseLong(s, 8);
        return "";
    }
}
