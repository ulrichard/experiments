// C++98
X::X(/*...*/) : mem1(init1), mem2(init2, init3) {/*...*/}

// C++11
X::X(/*...*/) : mem1{init1}, mem2{init2, init3} {/*...*/}



void draw_rect(rectangle);
 
// C++98
draw_rect(rectangle(myobj.origin, selection.extents));

// C++11
draw_rect({myobj.origin, selection.extents});
