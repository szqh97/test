use std::mem;
pub struct List<T> {
    head: Link<T>,
}

type Link<T> = Option<Box<Node<T>>>;


struct Node<T> {
    elem: T,
    next: Link<T>,
}


impl<T> List<T> {
    pub fn new() -> Self {
        List{head: None}
    }

    pub fn push(&mut self, elem: T) {
        let new_node = Box::new(Node {
            elem: elem,
            next: self.head.take(),
        });
        self.head = Some(new_node);
    }

    pub fn pop(&mut self) -> Option<T> {
        self.head.take().map(|node|{
            let node = *node;
            self.head = node.next;
            node.elem
        })

    }

    pub fn peek(&self) ->Option<&T> {
        self.head.as_ref().map(|node|{
            &node.elem
        })
        
    }

    pub fn peek_mut(&mut self) -> Option<&mut T> {
        self.head.as_mut().map(|node|{
            &mut node.elem
        })
        
    }
}

pub trait Drop {
    fn drop(&mut self);
}

impl<T> Drop for List<T>{
    fn drop(&mut self){
        let mut cur_link = self.head.take();
        while let Some(mut boxed_node) = cur_link {
            cur_link = self.head.take();
        }
    }
}

pub trait Iterator{
    type Item;
    fn next(&mut self) -> Option<Self::Item>; 
}

pub struct IntoIter<T>(List<T>); 

impl<T> List<T>{
    pub fn into_iter(self) -> IntoIter<T> {
        IntoIter(self)
    }
}

impl<T> Iterator for IntoIter<T> {
    type Item = T;
    fn next(&mut self) -> Option<Self::Item> {
        self.0.pop()
    }
}

pub struct Iter<'a, T: 'a> {
    next: Option<&'a Node<T>>,
}

impl<T> List<T> {
    pub fn iter(& self) -> Iter<T> {
        Iter{next:self.head.as_ref().map(|node| &**node)}
    }
}

impl<'a, T> Iterator for Iter<'a, T>{
    type Item = &'a T;
    fn next(& mut self) -> Option<Self::Item> {
        self.next.map(|node|{
            self.next = node.next.as_ref().map(|node| & **node);
            & node.elem
        })
    }
}

////// for iterMut
pub struct IterMut<'a, T: 'a> {
    next: Option<&'a mut Node<T>>,
}

impl<T> List<T>{
    pub fn iter_mut(&mut self) -> IterMut<T> {
        IterMut {next:self.head.as_mut().map(|node| &mut **node)}
    }
}

impl<'a, T> Iterator for IterMut <'a, T>{
    type Item = &'a mut T;
    fn  next(&mut self) -> Option<Self::Item> {
        self.next.take().map(|node|{
            self.next = node.next.as_mut().map(|node| &mut **node);
            &mut node.elem
        })
    }
}

#[cfg(test)]
mod test{
    use super::List;
    use second::Iterator;

    #[test]
    fn basic() {
        let mut list = List::new();
        assert_eq!(list.pop(), None);

        list.push(1);
        list.push(2);
        list.push(3);

        assert_eq!(list.pop(), Some(3));
        assert_eq!(list.pop(), Some(2));

        list.push(4);
        list.push(5);

        assert_eq!(list.pop(), Some(5));
        assert_eq!(list.pop(), Some(4));

        assert_eq!(list.pop(), Some(1));
        assert_eq!(list.pop(), None);
    }

    #[test]
    fn into_iter() {
        let mut list = List::new();
        list.push(1);
        list.push(2);
        list.push(3);
        let mut iter = list.into_iter();
        assert_eq!(iter.next(), Some(3));
        assert_eq!(iter.next(), Some(2));
        assert_eq!(iter.next(), Some(1));
    }

    #[test]
    fn iter() {
        let mut list = List::new();
        list.push(1);
        list.push(2);
        list.push(3);
        list.push(5);
        
        let mut iter = list.iter();
        assert_eq!(iter.next(), Some(&5));
        assert_eq!(iter.next(), Some(&3));
        assert_eq!(iter.next(), Some(&2));

        
    }

    //// for iterMut
    #[test]
    fn iter_mut() {
        let mut list = List::new();
        list.push(1);
        list.push(2);
        list.push(3);

        let mut iter = list.iter_mut();
        assert_eq!(iter.next(), Some(&mut 3));
        assert_eq!(iter.next(), Some(&mut 2));
        assert_eq!(iter.next(), Some(&mut 1));
    }

}
