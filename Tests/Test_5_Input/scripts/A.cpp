B b[10];
bool flag = false;

Create {
    for (int i = 0; i < 10; i++) {
        b[i] = create_object_B();
        b[i]&id = i;
    }
}

Destroy {

}

Update {
    if (!flag) {
        flag = true;
        for (int i = 0; i < 10; i++)
            destroy_object_B(b[i]);
    }
}

Draw3D {

}

Draw2D {

}
