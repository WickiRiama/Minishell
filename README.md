# Minishell

BUILTIN : TODO 

ENV: protection : si unset le premier maillon de la liste --> segfault
ENV: suppr la protection env == NULL car on doit pouvoir export UN SEUL maillon
ECHO: si "echo -n" || "echo -n -n" etc --> segfault
EXPORT: doublon si export avec "=-"
