module benchmark
    implicit none

    type benchmark_result
        real(kind = 8) :: start_time
        real(kind = 8) :: stop_time
    end type benchmark_result

    contains

        !----------------------------------------------------------------------
        ! compute the average over several result value
        type(benchmark_result) function result_average(results)
            implicit none
            type(benchmark_result),dimension(:),intent(in) :: results !results
            type(benchmark_result) ::av_result  !result for the average
            integer :: i  !loop index

            !initialize result value
            av_result%start_time = 0.d0
            av_result%stop_time  = 0.d0

            !run the main loop
            do i = 1,size(results)
               av_result%start_time = av_result%start_time + results(i)%start_time
               av_result%stop_time  = av_result%stop_time  + results(i)%stop_time
            end do

            !normalize result
            av_result%start_time = av_result%start_time/size(results)
            av_result%stop_time  = av_result%stop_time/size(results)

            result_average = av_result
            return 
        end function result_average

        !----------------------------------------------------------------------
        !compute the average of the duration
        real(kind=8) function duration_average(results)
            implicit none
            type(benchmark_result),dimension(:),intent(in) :: results
            real(kind=8) :: dav
            integer :: i

            dav = 0.d0
            do i=1,size(results)
               dav = dav + result_duration(results(i)) 
            end do

            dav = dav/size(results)
            duration_average = dav
            return
        end function duration_average

        !----------------------------------------------------------------------
        !compute the standard deviation from the duration
        real(kind=8) function duration_error(results)
            implicit none
            type(benchmark_result),dimension(:),intent(in) :: results
            real(kind = 8) :: dav,error_sum,d
            integer :: i 

            !compute the average
            dav = duration_average(results)
            
            !compute the error sum
            error_sum = 0.d0
            do i = 0,size(results)
                d = result_duration(results(i)) !compute the duration for this result

                error_sum = error_sum + (d-dav)**2
            end do

            duration_error = sqrt(((1.d0)/(size(results)-1))*error_sum)
            return 
        end function duration_error
        
        !----------------------------------------------------------------------
        !compute the duration for a result
        real(kind = 8) function result_duration(res)
            implicit none
            type(benchmark_result),intent(in) :: res
            real(kind =8) :: duration

            duration = res%stop_time - res%start_time

            result_duration = duration
            return
        end function result_duration

        !----------------------------------------------------------------------
        subroutine print_result(title,results)
            implicit none
            character(len=*),intent(in) :: title
            type(benchmark_result),dimension(:),intent(in) :: results
            real(kind = 8) :: r,r_error,r_error_p

            r = duration_average(results)
            r_error = duration_error(results)
            r_error_p = r_error*100.d0/r

            write(*,*) title,r,'(+-)',r_error,'(s)',r_error_p,'(%)'


        end subroutine print_result

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
