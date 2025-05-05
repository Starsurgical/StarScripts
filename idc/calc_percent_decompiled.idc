#include <idc.idc>

static main() {
  auto ea,x,num_functions,num_decompiled,c,segname;

  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  msg("RESULTS: %d / %d\n", num_decompiled, num_functions);

  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (strstr(segname, "gluBN") != -1) continue;
    if (strstr(segname, "net_bnet") != -1) continue;
    if (strstr(segname, "Modem") != -1) continue;
    if (strstr(segname, "statwrite") != -1) continue;
    if (strstr(segname, "codec") != -1) continue;
    if (strstr(segname, "League") != -1) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  msg("EXCLUDING BNET: %d / %d\n", num_decompiled, num_functions);


  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (strstr(segname, "gluBN") != -1) continue;
    if (strstr(segname, "net_bnet") != -1) continue;
    if (strstr(segname, "Modem") != -1) continue;
    if (strstr(segname, "statwrite") != -1) continue;
    if (strstr(segname, "codec") != -1) continue;
    if (strstr(segname, "League") != -1) continue;

    if (strstr(segname, "gluChat") != -1) continue;
    if (strstr(segname, "gluCreat") != -1) continue;
    if (strstr(segname, "gluJoin") != -1) continue;
    if (strstr(segname, "gluMap") != -1) continue;
    if (strstr(segname, "gluScore") != -1) continue;
    if (strstr(segname, "net_chat") != -1) continue;
    if (strstr(segname, "net_record") != -1) continue;
    if (strstr(segname, "replay") != -1) continue;
    if (strstr(segname, "uiMulti") != -1) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  msg("EXCLUDING MULTIPLAYER AND REPLAYS: %d / %d\n", num_decompiled, num_functions);


}
