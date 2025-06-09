#include <idc.idc>

static write_result(name, num_decompiled, num_functions) {
  auto ratio, pct, pct_fraction;

  ratio = 100 * 100 * num_decompiled / num_functions;
  pct = ratio / 100;
  pct_fraction = ratio % 100;

  msg("%s: %d / %d (%d.%02d%%)\n", name, num_decompiled, num_functions, pct, pct_fraction);
}

static is_bnet_segment(segname) {
  if (strstr(segname, "gluBN") != -1) return 1;
  if (strstr(segname, "net_bnet") != -1) return 1;
  if (strstr(segname, "Modem") != -1) return 1;
  if (strstr(segname, "statwrite") != -1) return 1;
  if (strstr(segname, "codec") != -1) return 1;
  if (strstr(segname, "League") != -1) return 1;
  if (strstr(segname, "win_") != -1) return 1;
  return 0;
}

static is_multiplayer_segment(segname) {
  if (strstr(segname, "gluChat") != -1) return 1;
  if (strstr(segname, "gluCreat") != -1) return 1;
  if (strstr(segname, "gluJoin") != -1) return 1;
  if (strstr(segname, "gluMap") != -1) return 1;
  if (strstr(segname, "gluScore") != -1) return 1;
  if (strstr(segname, "net_chat") != -1) return 1;
  if (strstr(segname, "net_chrm") != -1) return 1;
  if (strstr(segname, "net_sync") != -1) return 1;
  if (strstr(segname, "net_time") != -1) return 1;
  if (strstr(segname, "net_slot") != -1) return 1;
  if (strstr(segname, "net_misc") != -1) return 1;
  if (strstr(segname, "net_mgr") != -1) return 1;
  if (strstr(segname, "net_glue") != -1) return 1;
  if (strstr(segname, "netdesc") != -1) return 1;
  if (strstr(segname, "net_record") != -1) return 1;
  if (strstr(segname, "fd") != -1) return 1;
  if (strstr(segname, "filedist") != -1) return 1;
  if (strstr(segname, "uiMulti") != -1) return 1;
  if (strstr(segname, "filters") != -1) return 1;
  return 0;
}

static is_saveload_segment(segname) {
  if (strstr(segname, "replay") != -1) return 1;
  if (strstr(segname, "save") != -1) return 1;
  if (strstr(segname, "sai_LoadSave") != -1) return 1;
  if (strstr(segname, "gluLoad") != -1) return 1;
  if (strstr(segname, "Save") != -1) return 1;
  return 0;
}

static is_ai_segment(segname) {
  if (strstr(segname, "TAI_") != -1) return 1;
  if (strstr(segname, "sai_TownBuilder") != -1) return 1;
  if (strstr(segname, "SAI_Scripts") != -1) return 1;
  if (strstr(segname, "SAI_Main") != -1) return 1;
  if (strstr(segname, "SAI_Build") != -1) return 1;
  if (strstr(segname, "SAI_Banker") != -1) return 1;
  if (strstr(segname, "choke") != -1) return 1;
  if (strstr(segname, "ai_names") != -1) return 1;
  return 0;
}

static main() {
  auto ea,x,num_functions,num_decompiled,c,segname;

  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {
    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    num_functions = num_functions + 1;
    if (get_color(ea, CIC_FUNC) != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("RESULTS", num_decompiled, num_functions);


  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {
    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (is_bnet_segment(segname)) continue;

    num_functions = num_functions + 1;
    if (get_color(ea, CIC_FUNC) != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING BNET", num_decompiled, num_functions);


  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {
    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (is_bnet_segment(segname)) continue;
    if (is_multiplayer_segment(segname)) continue;

    num_functions = num_functions + 1;
    if (get_color(ea, CIC_FUNC) != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING MULTIPLAYER", num_decompiled, num_functions);

  
  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {
    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (is_bnet_segment(segname)) continue;
    if (is_multiplayer_segment(segname)) continue;
    if (is_saveload_segment(segname)) continue;

    num_functions = num_functions + 1;
    if (get_color(ea, CIC_FUNC) != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING SAVELOAD & REPLAYS", num_decompiled, num_functions);
  

  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {
    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (is_bnet_segment(segname)) continue;
    if (is_multiplayer_segment(segname)) continue;
    if (is_saveload_segment(segname)) continue;
    if (is_ai_segment(segname)) continue;

    num_functions = num_functions + 1;
    if (get_color(ea, CIC_FUNC) != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING COMPUTER AI", num_decompiled, num_functions);
}
