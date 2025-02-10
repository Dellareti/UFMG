public class FormattedInteger {
  public static final int HEX = 0;
  public static final int PLAIN = 1;
  public static final int OCTAL = 2;
  private int value;
  private int format;
  public FormattedInteger(int f) {
    format = f;
  }
  public int getInt() {
    return value;
  }
  public String getString() {
    String result = null;
    if (format == HEX)
      result = "0x" + Integer.toHexString(value);
    else if (format == PLAIN) 
      result = Integer.toString(value);
    else if (format == OCTAL)
      result = "0" + Integer.toOctalString(value);
    return result;
  }
  public void setInt(int v) {
    value = v;
  }
  public String setString(String s) {
    if (format == HEX) {
      if (!s.startsWith("0x"))
        return "Hex strings must start with \"0x\".";
      int i = 2;
      while (i < s.length()) {
        char c = s.charAt(i);
        if (!(('0' <= c && c <= '9') ||
              ('a' <= c && c <= 'f') ||
              ('A' <= c && c <= 'F')))
          return "Hex digits are 0..9 and A..F" + 
                 " (or a..f).";
        i++;
      }
      value = (int) Long.parseLong(s.substring(2),16);
    }
    else if (format == PLAIN) {
      boolean negative = false;
      if (s.charAt(0) == '-') {
        negative = true;
        s = s.substring(1);
      }
      else if (s.charAt(0) < '0' || s.charAt(0) > '9')
        return "First char must be a decimal digit" +
               " or a minus sign.";
      int i = 0;
      while (i < s.length()) {
        char c = s.charAt(i);
        if (!('0' <= c && c <= '9'))
          return "Decimal digits must be 0..9";
        i++;
      }
      value = Integer.parseInt(s);
      if (negative) value = -value;
    }
    else {
      if (s.charAt(0) != '0')
        return "Octal requires a leading zero.";
      int i = 0;
      while (i < s.length()) {
        char c = s.charAt(i);
        if (!('0' <= c && c <= '7'))
          return "Octal digits must be 0..7";
        i++;
      }
      value = (int) Long.parseLong(s,8);
    }
    return "";
  }
}
