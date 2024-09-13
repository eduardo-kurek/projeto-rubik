# Função para linkar rubik e OpenMP à um alvo
function(target_link_rubik_and_openmp target)
    target_link_libraries(${target} PRIVATE rubik)
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${target} PRIVATE OpenMP::OpenMP_CXX)
    endif()
endfunction()