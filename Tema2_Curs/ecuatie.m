function y = T(n)
  if n == 0
    y = 1;
  elseif n == 1
    y = 1;
  else
    y = y(n / 2) + y(n / 3) + 1
  endif
endfunction