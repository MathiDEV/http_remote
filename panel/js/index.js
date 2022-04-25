const admin = "9TT37VAmR\$sQHPmolSpEnzaKbCfovtEediM0wJdDK@euX4fEifU7pTHXZ8gB"
const codeModal = new Modal(document.getElementById("codeModal"));

$("#codeModal button").click(function () {
    codeModal.hide();
});
function show_file(ip, path, name) {
    $.post("http://localhost:8888/getfile.php", { admin: admin, ip: ip, dir: path }).done(function (file) {
        $("#codeModal pre code").html(hljs.highlightAuto(file).value);
        $("#codeModal h3").text(name);
        codeModal.show()
    }).fail(function (xhr) {
        data = xhr.responseText.split("\n")[0]
        $.notify({ title: data }, { style: "metro" })
    })
}

function breadcrumb(user, ip, path) {
    $("#breadcrumb").html(`<li id="rootuser" class="inline-flex items-center">
    <div class="flex items-center">
    <svg class="w-6 h-6 mr-1" fill="currentColor" viewBox="0 0 20 20" xmlns="http://www.w3.org/2000/svg"><path fill-rule="evenodd" d="M10 9a3 3 0 100-6 3 3 0 000 6zm-7 9a7 7 0 1114 0H3z" clip-rule="evenodd"></path></svg>
        <span
            path="." class="cursor-pointer inline-flex items-center text-sm font-medium text-gray-700 hover:text-gray-900 dark:text-gray-400 dark:hover:text-white">
            ${user}
        </span>
        </div>
    </li>`);
    let dirs = path.split("/")
    let tot_path = ".";
    for (i in dirs) {
        let dir = dirs[i];
        if (dir == "" || dir == ".") continue;
        let thpath = "", thcolor = "text-gray-400";
        if (i < dirs.length - 1) {
            thpath = "path=\"" + tot_path + "/" + dir + "\"";
            thcolor = "cursor-pointer";
        }

        tot_path += "/" + dir;
        $("#breadcrumb").append(`<li aria-current="page">
        <div class="flex items-center">
            <svg class="w-6 h-6 text-gray-400" fill="currentColor" viewBox="0 0 20 20"
                xmlns="http://www.w3.org/2000/svg">
                <path fill-rule="evenodd"
                    d="M7.293 14.707a1 1 0 010-1.414L10.586 10 7.293 6.707a1 1 0 011.414-1.414l4 4a1 1 0 010 1.414l-4 4a1 1 0 01-1.414 0z"
                    clip-rule="evenodd"></path>
            </svg>
            <span ${thpath} class="ml-1 text-sm ${thcolor} font-medium md:ml-2">${dir}</span>
        </div>
    </li>`);
    }
    $("#breadcrumb span[path]").click(function () {
        show_files(user, ip, $(this).attr("path"));
    })
}

function show_files(username, ip, path) {
    files = $.post("http://localhost:8888/listdir.php", { admin: admin, ip: ip, dir: path }).done(function (files) {
        breadcrumb(username, ip, path);
        $("#files").html("");
        for (file of files) {
            let icon = (file.type == "dir") ? "img/folder.png" : "img/file.png";
            $("#files").append(`<li path="${file.path}" filetype="${file.type}" name="${file.name}" class="cursor-pointer flex my-1"><img class="mr-1" src="${icon}">${file.name}</li>`);
        }
        $("#files li[filetype=\"dir\"]").click(function () {
            show_files(username, ip, $(this).attr("path"));
        });
        $("#files li[filetype=\"file\"]").click(function () {
            show_file(ip, $(this).attr("path"), $(this).attr("name"));
        });
    }).fail(function (xhr) {
        data = xhr.responseText.split("\n")[0]
        $.notify({ title: data }, { style: "metro" })
    })
}

$.post("http://localhost:8888/get_users.php", { admin: admin }).done(function (users) {
    for (ip in users) {
        if (users[ip].os == "Windows") {
            icon = "img/windows.png";
        } else if (users[ip].os == "Darwin") {
            icon = "img/macos.png";
        } else {
            icon = "img/linux.png";
        }

        let active_class = (users[ip].active ? "cursor-pointer" : "opacity-50");

        let user_elem = $(`<li user="${ip}" class="flex justify-between items-center bg-white mt-2 p-2 rounded transition w-96 ${active_class}"><div class="flex ml-2"><img src="${icon}" width="40" height="40" class="rounded-full"><div class="flex flex-col ml-2"><span class="font-medium text-black">${users[ip].name}</span><span class="text-sm text-gray-400">${ip}<span class="bg-gray-200 text-gray-800 text-sm font-medium mr-2 px-1 py-0.5 rounded dark:bg-blue-200 dark:text-blue-800 ml-1">${users[ip].port}</span></span></div></div><div class="flex flex-col items-center"><span class="text-gray-500 hover:underline"><a href="http://localhost:8888/trace?userip=${ip}" target="_blank">Trace</a></span><i class="fa fa-star text-green-400"></i></div></li>`)
        $("#user_list").append(user_elem)
    }
    $("#user_list li[user]:not(.opacity-50)").click(function (e) {
        if ($(e.target).is('a'))
            return
        $("#userfiles").fadeIn(200)
        let ip = $(this).attr("user")
        $("#userfiles button").unbind("click").click(function () {
            $(this).attr("disabled", "disabled").addClass(["cursor-not-allowed", "opacity-50"]);
            $.post("http://localhost:8888/mouli.php", { admin: admin, ip: ip }).done(function (res) {
                $.notify({ title: res }, { style: "metro", className: "success" })
                $("#userfiles button").attr("disabled", false).removeClass(["cursor-not-allowed", "opacity-50"]);
            }).fail(function (xhr) {
                data = xhr.responseText.split("\n")[0]
                $.notify({ title: data }, { style: "metro" })
            })
        });
        show_files(users[ip].name, ip, ".")
    })
}).fail(function (xhr) {
    data = xhr.responseText.split("\n")[0]
    $.notify({ title: data }, { style: "metro" })
})