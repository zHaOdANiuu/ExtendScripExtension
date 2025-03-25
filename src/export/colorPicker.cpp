#include "colorPicker.h"
#include "clamp.hpp"

int colorPicker(TaggedData* args, long argsLength, TaggedData* resultP)
{
    PF_PixelFloat color = { 1, 1, 0, 0 };
    if (argsLength >= 0) {
        int rgb = args[0].data.fltval;
        rgb = clamp(rgb, 0, 0xFFFFFF);
        color.red = (PF_FpShort)((rgb & 0xFF0000) >> 16) / 0xff;
        color.green = (PF_FpShort)((rgb & 0x00FF00) >> 8) / 0xff;
        color.blue = (PF_FpShort)((rgb & 0x0000FF)) / 0xff;
    }

    const char* title = (argsLength > 1) ? args[1].data.string : "Color Picker";

    AEGP_SuiteHandler suites(globalPicaBasicPtr);
    if (suites.AppSuite4()->PF_AppColorPickerDialog(title, &color, false, &color) == PF_Interrupt_CANCEL) {
        resultP->data.fltval = -1;
        return kESErrOK;
    }

    resultP->data.fltval = uint8(round(color.red * 0xff)) << 16 | uint8(round(color.green * 0xff)) << 8 | uint8(round(color.blue * 0xff));

    return kESErrOK;
}
