$.notify.addStyle("metro", {
    html:
        "<div>" +
            "<div class='text-wrapper'>" +
                "<div class='title' data-notify-html='title'/>" +
            "</div>" +
        "</div>",
    classes: {
        error: {
            "color": "#fafafa !important",
            "background-color": "#dc3545",
            "border": "1px solid #FF0026"
        },
        success: {
            "color": "#fafafa !important",
            "background-color": "#3fa745",
            "border": "1px solid #4DB149"
        },
        info: {
            "color": "#fafafa !important",
            "background-color": "#3da2b7",
            "border": "1px solid #1E90FF"
        },
        warning: {
            "background-color": "#f8c10b",
            "border": "1px solid #EEEE45"
        },
        black: {
            "color": "#fafafa !important",
            "background-color": "#343a3f",
            "border": "1px solid #000"
        },
        white: {
            "background-color": "#f8f9fa",
            "border": "1px solid #ddd"
        }
    }
});