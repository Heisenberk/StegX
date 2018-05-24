# Auteur : Pierre AYOUB
# ==============================================================================

# Crée une liste de tout les dossiers contenant un header à partir du dossier
# courant.
macro (HEADER_DIRECTORIES return_list)
    file (GLOB_RECURSE new_list *${INC_EXT})
    set (dir_list "")
    foreach (file_path ${new_list})
        get_filename_component (dir_path ${file_path} PATH)
        set (dir_list ${dir_list} ${dir_path})
    endforeach ()
    list (REMOVE_DUPLICATES dir_list)
    set (${return_list} ${dir_list})
endmacro ()
