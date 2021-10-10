int id;
bool flag = false;

Create {

}

Destroy {

}

Update {
    if (!flag) {
        flag = true;
        std::cout << id << std::endl;
    }

    if (id > 0) {
        A a = create_object_A();
        a&id = id - 1;
        id--;
    }
}

Draw3D {
}

Draw2D {

}
