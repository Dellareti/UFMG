public class PlainFormattedInteger extends AbstractFormattedInteger {
    @Override
    public String getString() {
        return Integer.toString(value);
    }
    
    @Override
    public String setString(String s) {
        boolean negative = false;
        String num = s;
        
        if (s.charAt(0) == '-') {
            negative = true;
            num = s.substring(1);
        } else if (s.charAt(0) < '0' || s.charAt(0) > '9') {
            return "First char must be a decimal digit or a minus sign.";
        }
        
        for (int i = 0; i < num.length(); i++) {
            char c = num.charAt(i);
            if (!('0' <= c && c <= '9')) {
                return "Decimal digits must be 0..9";
            }
        }
        
        value = Integer.parseInt(s);
        return "";
    }
}
