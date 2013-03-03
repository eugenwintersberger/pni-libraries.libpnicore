module benchmark
    implicit none

    type benchmark_result
        real(kind = 8) :: start_time
        real(kind = 8) :: stop_time
    end type benchmark_result

    contains

        !----------------------------------------------------------------------
        type(benchmark_result) function result_average(results)
            implicit none
            type(benchmark_result),dimension(:),intent(in) :: results
            type(benchmark_result) ::av_result
            integer :: i

            av_result%start_time = 0.
            av_result%stop_time  = 0.
            do i = 1,size(results)
               av_result%start_time = results(i)%start_time
               av_result%stop_time  = results(i)%stop_time
            end do

            result_average = av_result
            return 
        end function result_average
        
        !----------------------------------------------------------------------
        real(kind = 8) function result_duration(res)
            implicit none
            type(benchmark_result),intent(in) :: res
            real(kind =8) :: duration

            duration = res%stop_time - res%start_time

            result_duration = duration
            return
        end function result_duration

        !----------------------------------------------------------------------
        subroutine allocate_benchmark_results(nruns,results)
            implicit none
            integer,intent(in) :: nruns
            type(benchmark_result),dimension(:),allocatable,intent(inout) :: results
            integer :: mem_status,i

            !check if array is already allocated
            call deallocate_benchmark_results(results)

            !allocate memory
            allocate(results(nruns),stat=mem_status)

            !initialize data
            call reset_benchmark_results(results)


        end subroutine allocate_benchmark_results

        !----------------------------------------------------------------------
        subroutine reset_benchmark_results(results)
            implicit none
            type(benchmark_result),dimension(:),intent(inout) :: results
            integer :: i

            do i = 1,size(results)
                results(i)%start_time = 0.d0
                results(i)%stop_time  = 0.d0
            end do

        end subroutine reset_benchmark_results

        !----------------------------------------------------------------------
        subroutine deallocate_benchmark_results(results)
            implicit none
            type(benchmark_result),dimension(:),allocatable,intent(inout):: results
            integer :: mem_status

            if (allocated(results)) then
               deallocate(results,stat=mem_status) 
            end if

        end subroutine deallocate_benchmark_results

        !-----------------------------------------------------------------------
        subroutine run_benchmarks(proc,results)
            implicit none
            type(benchmark_result),dimension(:),intent(inout) :: results
            integer :: i

            do i = 1,size(results)
                call cpu_time(results(i)%start_time)
                call proc()
                call cpu_time(results(i)%stop_time)
            end do

        end subroutine run_benchmarks

end module benchmark

module arithmetics
    implicit none
    save

    real(kind = 8),dimension(:,:),allocatable,private :: a
    real(kind = 8),dimension(:,:),allocatable,private :: b
    real(kind = 8),dimension(:,:),allocatable,private :: c
    contains

        !----------------------------------------------------------------------
        subroutine run_add()
            implicit none
            c = a + b
        end subroutine run_add

        !----------------------------------------------------------------------
        subroutine run_sub()
            implicit none
            c = a - b
        end subroutine run_sub

        !----------------------------------------------------------------------
        subroutine run_mult()
            implicit none

            c = a*b
        end subroutine run_mult

        !----------------------------------------------------------------------
        subroutine run_div()
            implicit none

            c = a/b
        end subroutine run_div

        !----------------------------------------------------------------------
        subroutine run_all()
            implicit none

            c = a*b + (a-b)/a
        end subroutine run_all

        !-----------------------------------------------------------------------
        subroutine allocate_arithmetics(nx,ny)
            implicit none
            integer,intent(in) :: nx,ny
            integer :: mem_status
    
            !deallocate memory if necessary
            call deallocate_arithmetics()

            allocate(a(nx,ny),stat=mem_status)
            allocate(b(nx,ny),stat=mem_status)
            allocate(c(nx,ny),stat=mem_status)

        end subroutine allocate_arithmetics

        !-----------------------------------------------------------------------
        subroutine deallocate_arithmetics()
            implicit none
            integer :: mem_status

            if (allocated(a)) then
                deallocate(a,stat=mem_status)
            end if

            if (allocated(b)) then
                deallocate(b,stat=mem_status)
            end if

            if (allocated(c)) then
                deallocate(c,stat=mem_status)
            end if
        end subroutine deallocate_arithmetics

end module arithmetics

program farithmeticbm 
    use benchmark
    use arithmetics
    implicit none
    type(benchmark_result),dimension(:),allocatable :: results
    integer :: nx,ny,nruns
    type(benchmark_result) :: add_result,sub_result,div_result,mult_result
    type(benchmark_result) :: all_result

    nx = 5000
    ny = 5000
    nruns = 10

    !allocate memory
    call allocate_benchmark_results(nruns,results)
    call allocate_arithmetics(nx,ny)

    !run the add benchmarks    
    call run_benchmarks(run_add,results)
    add_result = result_average(results)
    call reset_benchmark_results(results)
        
    !run the sub benchmarks
    call run_benchmarks(run_sub,results)
    sub_result = result_average(results)
    call reset_benchmark_results(results)

    !run the div benchmarks
    call run_benchmarks(run_div,results)
    div_result = result_average(results)
    call reset_benchmark_results(results)

    !run the mult benchmarks
    call run_benchmarks(run_mult,results)
    mult_result = result_average(results)
    call reset_benchmark_results(results)

    !run the all benchmark
    call run_benchmarks(run_all,results)
    all_result = result_average(results)
    call reset_benchmark_results(results)

    write(*,*) 'add result:  ',result_duration(add_result) 
    write(*,*) 'sub result:  ',result_duration(sub_result)
    write(*,*) 'div result:  ',result_duration(div_result)
    write(*,*) 'mult result: ',result_duration(mult_result)
    write(*,*) 'all result:  ',result_duration(all_result)


    !in the end we have to free everything
    call deallocate_benchmark_results(results)
    call deallocate_arithmetics()

end program farithmeticbm
