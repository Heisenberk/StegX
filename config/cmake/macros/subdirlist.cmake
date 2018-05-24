# Auteur : Pierre AYOUB
# ==============================================================================

# Inscrit sous forme de liste, dans "result", le nom des différents répertoires
# contenus dans "curdir".
macro (SUBDIRLIST result curdir)
    file (GLOB children RELATIVE ${curdir} ${curdir}/*)
    set (dirlist "")
    foreach (child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            list (APPEND dirlist ${child})
        endif ()
    endforeach ()
    set (${result} ${dirlist})
endmacro ()

