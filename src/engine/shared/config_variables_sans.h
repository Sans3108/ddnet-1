#ifndef MACRO_CONFIG_INT
#error "The config macros must be defined"
#define MACRO_CONFIG_INT(Name, ScriptName, Def, Min, Max, Save, Desc) ;
#define MACRO_CONFIG_COL(Name, ScriptName, Def, Save, Desc) ;
#define MACRO_CONFIG_STR(Name, ScriptName, Len, Def, Save, Desc) ;
#endif

// Sans client
MACRO_CONFIG_INT(SansGreetOnStart, s_greet_on_start, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "If the client greet you in F1 console on startup.")