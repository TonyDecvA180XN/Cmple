int idx;

Create {

}

Destroy {

}

Update {

}

Draw3D {

}

Draw2D {
    draw_text(std::to_string(idx), FT_CALIBRI, 700.0, 100.0 + idx * 32.0, 0.0, 1.0, 24.0, 0.3, 1.0, 0.3);
}
