#!/usr/bin/env gawk
BEGIN{
    FIELDWIDTHS = "9 9 17 9 7 7 5 20"
    }
NR > 2 {
    idle = $5
    sub(/^ */, "", idle)
    if (idle == "")
        idle = 0
    if (idle ~ /:/)
    {
        split(idle, t, ":")
        idle = t[1] * 60 + t[2]
    }
    if (idle ~ /days/)
        idle *= 24 * 60 * 60
    print $1, $2, $5, idle 
    }

