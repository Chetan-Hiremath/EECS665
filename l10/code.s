.globl _start

.data
nums:      .quad 0, 0, 0           # Declare "array" of 3 8-byte numbers
                                   #   all initialized to 0
num_count: .quad 3                 # Declare a counter variable
                                   #   i.e. the "array size"
sum:       .quad 0                 # Declare a variable to keep the sum
                                   #   which is returned as the exit code
.text
_start:                            


rand_loop_init:
            movq $nums, %r12       # set up r12 as nums element pointer
            movq (num_count), %r13 # set up r13 as loop iterator (countdown)
rand_loop_head:
            cmpq $0, %r13          # loop predicate: check if iterator == 0
            je   rand_loop_after   # skip loop body if countdown is 0
rand_loop_body:
            # call sys_getrandom, which gets a pointer and fills that
            # location with random bytes
            movq $318, %rax    # syscall choice: sys_getrandom
	        movq %r12, %rdi    # syscall arg 1: destination pointer
	        movq $1, %rsi      # syscall arg 2: fill 1 random byte
            movq $0, %rdx      # syscall arg 3: flags (none)
            syscall
	    # clamp the random value
            movq (%r12), %r10  # load the random value to a temp register
            andq $0x0f, %r10   # apply the mask to the temp register
	        movq %r10, (%r12)  # overwrite the original value with clamped
	    # prepare for the next loop iteration
            addq $8, %r12      # increment nums ptr to the next 8-byte index
            subq $1, %r13      # decrement the loop iterator
            jmp rand_loop_head # go back to the head of the loop
rand_loop_after:
            nop                # finished with the loop

###### YOUR CODE BELOW ############

sum_loop_init:
            # Tasks (initialize loop)
            # 1. set up a register as a nums element pointer
            movq $nums, %r14
            # 2. set up a register as a loop iterator over nums "array" length
            movq (num_count), %r15
sum_loop_head:
            # Tasks (evaluate for the loop control):
            # 1. use the cmpq instruction to check if the iterator
            #    has gone through the whole of nums
            cmpq $0, %r15
            # 2. if the iterator has completed, skip the loop body
            je   sum_loop_after
sum_loop_body:
            # Tasks (add the current element to the running sum):
            # 1. load the current sum var into register
            movq (%r14), %r12
            # 2. load the current nums element into register
            nop
            # 3. add the registers
            nop
            # 4. save the destination register back to running sum var
            nop

            # Tasks (prepare for the next loop iteration)
            # 1. move the nums element pointer forward by 1 element
            nop
            # 2. update the iterator
            nop
            # 3. go back to the loop head
            nop
sum_loop_after:
            #Tasks (fallthrough)
            # 0. No action needed 
            nop

###### YOUR CODE ABOVE ############

prog_exit:   
            # invoke the exit syscall with the value of the sum variable
            movq $60, %rax    # syscall choice sys_exit
            movq (sum), %rdi  # syscall arg 1: exit value
            syscall
