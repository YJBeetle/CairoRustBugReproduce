#include <stdio.h>
#include <cairo.h>
#include <cairo-pdf.h>

cairo_status_t write_data(void *closure, const unsigned char *data, unsigned int length)
{
    FILE *file = (FILE *)closure;
    if (fwrite(data, 1, length, file) != length) {
      return CAIRO_STATUS_WRITE_ERROR;
    }

    return CAIRO_STATUS_SUCCESS;
}

void paint(cairo_surface_t *surface)
{
    cairo_t *cr = cairo_create(surface);

    cairo_surface_t *surface2 = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);
    cairo_t *cr2 = cairo_create(surface2);
    cairo_set_source_rgb(cr2, 0., 1., 0.);
    cairo_rectangle(cr2, 0., 0., 200., 200.);
    cairo_fill(cr2);
    cairo_set_source_surface(cr, surface2, 100., 100.);
    cairo_paint(cr);

    cairo_surface_t *surface3 = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);
    cairo_t *cr3 = cairo_create(surface3);
    cairo_set_source_rgb(cr3, 0., 0., 1.);
    cairo_rectangle(cr3, 0., 0., 200., 200.);
    cairo_fill(cr3);
    cairo_set_source_surface(cr, surface3, 200., 200.);
    cairo_paint(cr);

    cairo_destroy(cr3);
    cairo_surface_destroy(surface3);
    cairo_destroy(cr2);
    cairo_surface_destroy(surface2);
    cairo_destroy(cr);
}

int main()
{
    {
        printf("create PNG\n");
        cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 500, 500);
        paint(surface);
        FILE *file = fopen("out.png", "wb");
        cairo_surface_write_to_png_stream(surface, write_data, (void *)file);
        fclose(file);
        cairo_surface_destroy(surface);
    }
    {
        printf("create PDF\n");
        FILE *file = fopen("out.pdf", "wb");
        cairo_surface_t *surface = cairo_pdf_surface_create_for_stream(write_data, (void *)file, 500., 500.);
        paint(surface);
        cairo_surface_finish(surface);
        fclose(file);
        cairo_surface_destroy(surface);
    }
}
