use cairo::{Context, ImageSurface, PdfSurface, RecordingSurface, Surface};

fn paint(surface: &Surface) {
    let cr = Context::new(surface).unwrap();

    let surface2 = RecordingSurface::create(cairo::Content::Alpha, None).unwrap();
    let cr2 = Context::new(&surface2).unwrap();
    cr2.set_source_rgb(0., 1., 0.);
    cr2.rectangle(0., 0., 200., 200.);
    cr2.fill().unwrap();
    cr.set_source_surface(&surface2, 100., 100.).unwrap();
    cr.paint().unwrap();

    let surface3 = RecordingSurface::create(cairo::Content::Alpha, None).unwrap();
    let cr3 = Context::new(&surface3).unwrap();
    cr3.set_source_rgb(0., 0., 1.);
    cr3.rectangle(0., 0., 200., 200.);
    cr3.fill().unwrap();
    cr.set_source_surface(&surface3, 200., 200.).unwrap();
    cr.paint().unwrap();
}

fn main() {
    {
        println!("create PNG");
        let surface = ImageSurface::create(cairo::Format::ARgb32, 500, 500).unwrap();
        paint(&surface);
        let mut f = std::fs::File::create("out.png").unwrap();
        surface.write_to_png(&mut f).unwrap();
    }

    {
        println!("create PDF");
        let f = std::fs::File::create("out.pdf").unwrap();
        let surface = PdfSurface::for_stream(500., 500., f).unwrap();
        paint(&surface);
        surface.finish();
    }
}
