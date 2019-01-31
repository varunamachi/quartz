function qzLogJSON(any) {
    const content = JSON.stringify(any);
    if (window.qzwrapper) {
        window.qzwrapper.print(cnt);
    }
}

//window.setEditorContent = function(cnt) {
//    if (window.editor) {
//        window.editor.setValue(cnt);
//    }
//}

//window.setLanguage = function(lng) {
//    if (window.editor) {
//           monaco.editor.setModelLanguage(window.editor.getModel(), lng);
//    }
//}



//window.setTheme = function(thm) {
//    if (window.editor) {
//        monaco.editor.setTheme(window.editor.getModel(), thm);
//    }
//}

