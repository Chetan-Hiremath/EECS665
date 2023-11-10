set breakpoint pending on
set confirm off
file ./cmmc
break jeff::Err::report
commands
	where
end
break jeff::InternalError::InternalError
commands
	where
end
break jeff::ToDoError::ToDoError
commands
	where
end

define p5
  set args p5_tests/$arg0.cmm -c
  run
end
