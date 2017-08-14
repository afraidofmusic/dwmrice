# Aliases
alias ls='ls --color'

export PATH=$PATH:/home/can/bin
export EDITOR="/usr/bin/vi"
export BROWSER="firefox"
# Bash Prompt
export PS1="\[$(tput bold)\]\[$(tput setaf 1)\] \W\[$(tput setaf 7)\] λ \[$(tput sgr0)\]"
export PS2="\[$(tput bold)\]\[$(tput setaf 1)\] > \[$(tput sgr0)\]"
# XINIT
if [ -z "$DISPLAY" ] && [ -n "$XDG_VTNR" ] && [ "$XDG_VTNR" -eq 1 ]; then
      exec startx
fi
# BASE16
BASE16_SHELL=$HOME/.config/base16-shell/
[ -n "$PS1" ] && [ -s $BASE16_SHELL/profile_helper.sh ] && eval "$($BASE16_SHELL/profile_helper.sh)"
# TMUX
if which tmux >/dev/null 2>&1; then
    #if not inside a tmux session, and if no session is started, start a new session
    test -z "$TMUX" && (tmux attach || tmux new -s st)
fi
