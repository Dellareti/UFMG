public class HexFormattedInteger extends AbstractFormattedInteger {
    @Override
    public String getString() {
        return "0x" + Integer.toHexString(value);
    }
    
    @Override
    public String setString(String s) {
        if (!s.startsWith("0x")) {
            return "Hex strings must start with \"0x\".";
        }
        
        for (int i = 2; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!(('0' <= c && c <= '9') ||
                  ('a' <= c && c <= 'f') ||
                  ('A' <= c && c <= 'F'))) {
                return "Hex digits are 0..9 and A..F (or a..f).";
            }
        }
        
        value = (int) Long.parseLong(s.substring(2), 16);
        return "";
    }
}
