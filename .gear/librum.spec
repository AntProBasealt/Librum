%define _unpackaged_files_terminate_build 1

Name: librum
Version: 0.4.6
Release: alt1
Summary: Librum is an application designed to make reading enjoyable and straightforward for you.
License: %gpl2only
Group: Development/Other
Url: https://github.com/Librum-Reader/Librum
Source: %name-%version.tar

BuildRequires(pre): rpm-build-licenses cmake gcc gcc-c++

%description
It's more than just an e-book reader. With Librum, you can manage your own online library and access it from all your devices at any time. It offers features like note-taking, bookmarking, highlighting, while being able to customise the application to look and feel exactly how you want it to. Librum also provides free access to over 70,000 books and your reading statistics while being free and completely open source.

 

%prep
%setup -q

%build
%cmake -DCMAKE_BUILD_TYPE=Release
%cmake_build

%install
%cmakeinstall_std PREFIX=%_prefix DESTDIR=%buildroot

%files
%_bindir/*

%changelog
* Wed May 31 2023 Anton Protopopov <antpro@basealt.ru> 0.4.6-alt1
- test
