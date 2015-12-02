use std::rc::Rc;
struct Owner {
    name: String,
}

struct Gadget {
    id:i32,
    owner: Rc<Owner>
}

fn main() {
    let gadget_owner: Rc<Owner> = Rc::new(
        Owner {name: String::from("Gadget Man")}
    );

    let gadget1 = Gadget {id:1, owner: gadget_owner.clone()};
    let gadget2 = Gadget {id:2, owner: gadget_owner.clone()};
    drop(gadget_owner);
}
