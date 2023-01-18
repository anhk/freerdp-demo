#include <stdio.h>
#if __APPLE__
#include <TargetConditionals.h>
#endif
#include <freerdp/client.h>
#include <freerdp/freerdp.h>
#include <freerdp/gdi/gdi.h>

#include "showhex.c"

FREERDP_LOCAL rdpChannels* freerdp_channels_new(freerdp* instance);

static BOOL global_init(void)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    return true;
}

static void global_uninit(void)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
}

static BOOL client_new(freerdp* instance, rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    return true;
}

static void client_free(freerdp* instance, rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
}

static int client_start(rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    HANDLE handles[64] = { 0 };
    DWORD waitStatus;

    if (!freerdp_connect(context->instance)) {
        printf("freerdp_connect return false\n");
        return 0;
    }

    while (!freerdp_shall_disconnect(context->instance)) {
        DWORD r = freerdp_get_event_handles(context, handles, 64);
        if (r == 0) {
            printf("freerdp_get_event_handles failed\n");
            break;
        }
        // printf("[%s:%d] %s get event: %d\n", __FILE__, __LINE__, __FUNCTION__,
        // r);

        if ((waitStatus = WaitForMultipleObjects(r, handles, FALSE, 250)) == WAIT_FAILED) {
            printf("[%s:%d] %s, WaitForMultipleObjects: %d", __FILE__, __LINE__, __FUNCTION__, waitStatus);
            break;
        } else if (waitStatus == WAIT_TIMEOUT) {
            continue; // TODO: timeout, maybe break;
        }

        if (!freerdp_check_event_handles(context)) {
            fprintf(stderr, "Failed to check FreeRDP file descriptor\n");
            break;
        }
    }
    return 0;
}

static int client_stop(rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    return 0;
}

static BOOL pre_connect(freerdp* instance)
{
    rdpSettings* settings = instance->settings;
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    settings->OsMajorType = OSMAJORTYPE_UNIX;
    settings->OsMinorType = OSMINORTYPE_NATIVE_XSERVER;
    // settings->RemoteFxCodec = 0;
    settings->FastPathOutput = 1;
    settings->ColorDepth = 32; // 16;
    // settings->FrameAcknowledge = 1;
    // settings->LargePointerFlag = 1;
    settings->BitmapCacheV3Enabled = 0;
    settings->BitmapCachePersistEnabled = 0;

    // settings->OrderSupport[NEG_DSTBLT_INDEX] = TRUE;
    // settings->OrderSupport[NEG_PATBLT_INDEX] = TRUE;
    // settings->OrderSupport[NEG_SCRBLT_INDEX] = TRUE;
    // settings->OrderSupport[NEG_OPAQUE_RECT_INDEX] = TRUE;
    // settings->OrderSupport[NEG_DRAWNINEGRID_INDEX] = FALSE;
    // settings->OrderSupport[NEG_MULTIDSTBLT_INDEX] = FALSE;
    // settings->OrderSupport[NEG_MULTIPATBLT_INDEX] = FALSE;
    // settings->OrderSupport[NEG_MULTISCRBLT_INDEX] = FALSE;
    // settings->OrderSupport[NEG_MULTIOPAQUERECT_INDEX] = TRUE;
    // settings->OrderSupport[NEG_MULTI_DRAWNINEGRID_INDEX] = FALSE;
    // settings->OrderSupport[NEG_LINETO_INDEX] = TRUE;
    // settings->OrderSupport[NEG_POLYLINE_INDEX] = TRUE;
    // settings->OrderSupport[NEG_MEMBLT_INDEX] = settings->BitmapCacheEnabled;

    // settings->OrderSupport[NEG_MEM3BLT_INDEX] = FALSE;

    // settings->OrderSupport[NEG_MEMBLT_V2_INDEX] =
    // settings->BitmapCacheEnabled; settings->OrderSupport[NEG_MEM3BLT_V2_INDEX]
    // = FALSE; settings->OrderSupport[NEG_SAVEBITMAP_INDEX] = FALSE;
    // settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = TRUE;
    // settings->OrderSupport[NEG_FAST_INDEX_INDEX] = TRUE;
    // settings->OrderSupport[NEG_FAST_GLYPH_INDEX] = TRUE;

    // settings->OrderSupport[NEG_POLYGON_SC_INDEX] = FALSE;
    // settings->OrderSupport[NEG_POLYGON_CB_INDEX] = FALSE;

    // settings->OrderSupport[NEG_ELLIPSE_SC_INDEX] = FALSE;
    // settings->OrderSupport[NEG_ELLIPSE_CB_INDEX] = FALSE;

    settings->GlyphSupportLevel = GLYPH_SUPPORT_NONE;

    if (instance->context->cache == NULL) {
        instance->context->cache = cache_new(instance->settings);
    }
    printf("[%s:%d] %s [end]\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}

BOOL bitmap_new(rdpContext* context, rdpBitmap* bitmap)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}

void bitmap_free(rdpContext* context, rdpBitmap* bitmap)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
}

BOOL bitmap_paint(rdpContext* context, rdpBitmap* bitmap)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    if (bitmap->data != NULL) {
        int width = bitmap->right - bitmap->left + 1;
        int height = bitmap->bottom - bitmap->top + 1;

        show_hex(bitmap->data, 64);
        printf("[%s] w: %d, h: %d, len: %d\n", __FUNCTION__, width, height, bitmap->length);
    }

    return true;
}

// BOOL bitmap_decompress(rdpContext* context, rdpBitmap* bitmap, const BYTE* data, UINT32 width, UINT32 height,
//     UINT32 bpp, UINT32 length, BOOL compressed, UINT32 codec_id)
// {
//     printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
//     return true;
// }

BOOL bitmap_setsurface(rdpContext* context, rdpBitmap* bitmap, BOOL primary)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}

// BOOL glyph_new(rdpContext* context, const rdpGlyph* glyph)
// {
//     return true;
// }
// void glyph_free(rdpContext* context, rdpGlyph* glyph)
// {
// }
// BOOL glyph_draw(rdpContext* context, const rdpGlyph* glyph, INT32 x, INT32 y, INT32 w, INT32 h, INT32 sx, INT32 sy,
//     BOOL fOpRedundant)
// {
//     return true;
// }
// BOOL glyph_begin_draw(rdpContext* context, INT32 x, INT32 y, INT32 width, INT32 height, UINT32 bgcolor, UINT32 fgcolor,
//     BOOL fOpRedundant)
// {
//     return true;
// }
// BOOL glyph_end_draw(rdpContext* context, INT32 x, INT32 y, INT32 width, INT32 height, UINT32 bgcolor, UINT32 fgcolor)
// {
//     return true;
// }

// BOOL pointer_new(rdpContext* context, rdpPointer* pointer)
// {
//     return true;
// }
// void pointer_free(rdpContext* context, rdpPointer* pointer)
// {
// }
// BOOL pointer_set(rdpContext* context, const rdpPointer* pointer)
// {
//     return true;
// }
// BOOL pointer_set_null(rdpContext* context)
// {
//     return true;
// }
// BOOL pointer_set_default(rdpContext* context)
// {
//     return true;
// }

static BOOL register_graphics(rdpGraphics* graphics)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    rdpBitmap bitmap = *graphics->Bitmap_Prototype;

    bitmap.size = sizeof(rdpBitmap);
    bitmap.New = bitmap_new;
    bitmap.Free = bitmap_free;
    bitmap.Paint = bitmap_paint;
    // bitmap.Decompress = bitmap_decompress;
    bitmap.SetSurface = bitmap_setsurface;
    graphics_register_bitmap(graphics, &bitmap);
    printf("[%s:%d] %s [bitmap]\n", __FILE__, __LINE__, __FUNCTION__);

    // rdpGlyph glyph = *graphics->Glyph_Prototype;
    // glyph.size = sizeof(rdpGlyph);
    // glyph.New = glyph_new;
    // glyph.Free = glyph_free;
    // glyph.Draw = glyph_draw;
    // glyph.BeginDraw = glyph_begin_draw;
    // glyph.EndDraw = glyph_end_draw;
    // graphics_register_glyph(graphics, &glyph);

    // rdpPointer pointer = *graphics->Pointer_Prototype;
    // pointer.size = sizeof(rdpPointer);
    // pointer.New = pointer_new;
    // pointer.Free = pointer_free;
    // pointer.Set = pointer_set;
    // pointer.SetNull = pointer_set_null;
    // pointer.SetDefault = pointer_set_default;
    // graphics_register_pointer(graphics, &pointer);

    return TRUE;
}

BOOL update_begin_paint(rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    rdpGdi* gdi = context->gdi;

    if (gdi && gdi->primary && gdi->primary->hdc && gdi->primary->hdc->hwnd && gdi->primary->hdc->hwnd->invalid) {
        printf("[%s:%d] %s, set gdi->primary->hdc->hwnd->invalid->null = TRUE\n", __FILE__, __LINE__, __FUNCTION__);
        gdi->primary->hdc->hwnd->invalid->null = TRUE;
    }

    printf("[%s:%d] %s [end]\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}
BOOL update_end_paint(rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return TRUE;
}

BOOL update_play_sound(rdpContext* context, const PLAY_SOUND_UPDATE* play_sound)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}
BOOL update_set_keyboard_indicators(rdpContext* context, UINT16 led_flags)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}

BOOL update_desktop_resize(rdpContext* context)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}
BOOL update_set_keyboard_imestatus(rdpContext* context, UINT16 imeId, UINT32 imeState, UINT32 imeConvMode)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    return true;
}

static void register_update_callbacks(rdpUpdate* update)
{
    update->BeginPaint = update_begin_paint;
    update->EndPaint = update_end_paint;
    update->PlaySound = update_play_sound;
    update->DesktopResize = update_desktop_resize;
    update->SetKeyboardIndicators = update_set_keyboard_indicators;
    update->SetKeyboardImeStatus = update_set_keyboard_imestatus;
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
}

static BOOL post_connect(freerdp* instance)
{
    if (!gdi_init(instance, PIXEL_FORMAT_XRGB32)) {
        return FALSE;
    }
    register_graphics(instance->context->graphics);
    register_update_callbacks(instance->update);

    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    return true;
}

BOOL authenticate(freerdp* instance, char** username, char** password, char** domain)
{
    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);
    return true;
}

int main(int argc, char** argv)
{
    RDP_CLIENT_ENTRY_POINTS ep;
    memset(&ep, 0, sizeof(ep));

    ep.Size = sizeof(ep);
    ep.Version = RDP_CLIENT_INTERFACE_VERSION;
    ep.ContextSize = sizeof(rdpContext);
    ep.GlobalInit = global_init;
    ep.GlobalUninit = global_uninit;
    ep.ClientNew = client_new;
    ep.ClientFree = client_free;
    ep.ClientStart = client_start;
    ep.ClientStop = client_stop;

    rdpContext* ctx = freerdp_client_context_new(&ep);
    rdpSettings* settings = ctx->instance->settings;

    settings->ServerHostname = "10.226.239.200";
    settings->Username = "administrator";
    settings->Password = "xThXxsP7mQ0Xufjux";
    settings->IgnoreCertificate = true;

    ctx->instance->PreConnect = pre_connect;
    ctx->instance->PostConnect = post_connect;
    ctx->instance->Authenticate = authenticate;
    // ctx->instance->VerifyCertificate = ; // 验证证书

    printf("[%s:%d] %s\n", __FILE__, __LINE__, __FUNCTION__);

    // freerdp_connect(ctx->instance);
    // client_start(ctx);
    freerdp_client_start(ctx);
    printf("[%s:%d] %s after [start]\n", __FILE__, __LINE__, __FUNCTION__);

    return 0;
}

