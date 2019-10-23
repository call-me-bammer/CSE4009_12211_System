
1. 과제 설명
    malloc, free, realloc을 직접 구현하는 숙제입니다. 

    코드 작업과 주석 작업이 있습니다.
    
    코드 작업은 mm.c 파일에 있는 빈 펑션인 malloc, free, realloc을 문서에서 설명하는 기능으로 작동하도록 
    코드를 채워 주시면 됩니다. mm.c 파일안에 자유롭게 추가적인 펑션을 생성하거나 디파인 할 수 있지만 malloc의 
    실제 구현을 배울 수 있도록 하기위해 library를 통한 malloc사용과 어레이 등에 대한(자세한 리스트는 함께 
    제공되는 pdf 참고) 사용이 제한되어집니다. 
    
    
    기본적으로 heap사이즈를 키울 수 있는 펑션인 mem_sbrk펑션이 제공되어지고 이를 통해 공간을 확장하여 그 공간에 
    배치하시면 됩니다. 확장만 가능하고 heap에 대한 직접적인 free는 제공되지 않기에 free를 구현하실 떼에는 free된 
    공간이 allocation된 공간인지 아닌지 알 수 있도록 하고 접근할 수 있도록 하여 이후 malloc을 통해 공간을 할당할 
    떼 그 공간에 접근하여 배치할 수 있도록 하여야 합니다. 
    한 예로서 이를 위해 malloc을 통해 공간을 할당할 적에 공간이 free인지를 확인할 플래그 공간과 그 free된 공간을 이후 
    malloc에서 접근할 수 있도록 공간크기에 대한 정보를 담는 header공간을 포함하여서 공간을 주어 공간끼리 linked list처럼 
    연결을 하여 접근할 수 있도록 하여 이후에 free된 공간에 malloc을 통해 다시 접근하여 채우도록 하여야 합니다(다른 방식으로 
    구현하시어도 상관없습니다.). 
    
    구현을 쉽게 하도록 돕기 위하여 implicit free list 구조를 베이스 로한 서포트 펑션들과 그에 대한mm_init펑션이 
    mm.c파일 안에 제공되어집니다. 구현을 돕기 위해 제공되어지는 펑션들일 뿐 포인터나 트리 같은 다른 구조를 베이스로 하여 
    만드 셔도 상관없습니다. Implicit free list 구조는 공간을 할당할 때 free인지에 대한 flag와 앞뒤의 공간크기에 
    대한 정보를 담는 header와 footer라는 것을 두어서 공간을 앞뒤의 공간으로 접근할 수 있도록 하여 이후에 공간을 순차적으로 
    돌면서 free공간을 찾을 수 있도록 하였습니다. 
    
    주석은 구현하신 코드에 대하여 주석을 다라 주시면 됩니다

    총 점수는 65만점이고 correctness 20점, performance 35점, 주석 10점입니다.
    Correctness는 11개의 test input이 overflow없이 결과가 정상적으로 되어지면 20점으로 주어지며
    Correctness를 다 만족한 다면 이후에는 performance를 검사하여 점수를 주어지게 됩니다.
    Performance는 코드의 space utilization과 throughput을 보고 점수가 주어지게 됩니다.
    그리고 코드에 대한 주석으로 10점이 주어집니다.


	코드는 Gitlab에 2019/10/27 11:59PM 까지 올려주시기 바립니다.
	(gitLab에 업로드가 가능한지 미리 확인 부탁드립니다.)
	코드를 올릴때는 assignment2/mm.c 형태로 업로드 하시면 됩니다. (assignment2/mm.c 파일만 제출)
	mm.c 코드는 ./mdriver -v 이 에러없이 정상적으로 돌아가는것을 확인한후 제출하셔야 합니다. 
	제출이 이와 다를시 점수에 불이익이 있을수 있습니다.
	
	24시간까지 늦게 제출하는 경우에 50% 감점이며 24시간 이후 제출은 0점입니다.

2. 과제 수행 및 테스트 방법

	2.1 malloclab-handout 디렉터리로 이동
	2.2 mm.c 파일을 에디터로 오픈 
	2.3 수정 후 저장
    2.4 make입력으로 make처리
	2.5 ./mdriver -v 실행
	2.6 실행 결과를 확인 
	
	주의사항 : malloclab.pdf에서 허용하는 구현만 사용 해야 함. (malloc관련 라이브러리 사용불가)

그 외 세부 사항은 malloc-handout/malloclab.pdf 파일 참조

3. driver.pl 실행 시 에러가 발생하는 경우 
	3.1 라이브러리 설치
		sudo apt-get install g++-multilib
		sudo apt-get install make

		위의 패키지 설치후 에러가 발생 시 
			sudo apt-get update
			sudo apt-get upgrade
			sudo apt-get install g++-multilib
			sudo apt-get install make

	3.2 권한 설정
		malloc-handout 디렉터리로 이동후
		chmod +x *
	
4. 기타 사항
	다른 문의 사항이 있으신경우 92hyungjun@gmail.com 로 연락 부탁드립니다.
	
    과제에 대한 자세한 내용은 malloclab.pdf파일을 참조하세요.


