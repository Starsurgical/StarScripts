#include <idc.idc>

static main() {
    auto x;
    auto begin;
    auto end;
    auto flags;
    
    begin = read_selection_start();
    end = read_selection_end();
    
    if ( begin != BADADDR && end != BADADDR )
    {
        for ( x=begin; x<end; )
        {
            flags = GetFunctionFlags(x);
            SetFunctionFlags(x, flags | FUNC_LIB);
            
            x = NextFunction(x+1);
        }
    }
    else
    {
        x = ScreenEA();
        flags = GetFunctionFlags(x);
        SetFunctionFlags(x, flags | FUNC_LIB);
    }
    
    Refresh();
}
