public abstract class AbstractFormattedInteger implements FormattedInteger {
    protected int value;
    
    @Override
    public int getInt() {
        return value;
    }
    
    @Override
    public void setInt(int value) {
        this.value = value;
    }
}
