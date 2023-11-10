set breakpoint pending on
set confirm off
file ./jeffc
break jeff::Err::report
commands
	where
end
break jeff::ToDoError::ToDoError
commands
	where
end
break jeff::InternalError::InternalError
commands
	where
end

define p2
  set args p2_tests/$arg0.jeff -u
  run
end
