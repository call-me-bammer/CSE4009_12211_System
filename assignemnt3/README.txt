
1. 과제 설명

    Shell program을 직접 구현하는 숙제입니다
    이번숙제에서 해야 할 작업은 코드작업과 리포트 작업이 있습니다

    코드 작업은 주어진 shell programming code인 tsh.c에서 비어 있는 펑션들인 eval, built in command, waitfg을 문서에서 
    설명하는 기능으로 작동하도록 코드를 채워 주시면 됩니다. 그리고 구현을 쉽게 하기위해 시그널, job, bgfg변환을 서포팅하는 펑션들이 제공되어집니다. 
    
    이 shell program의 동작은 명령어를 받아서 shell program에서 인식하여 
        직접 다루도록 한 built in command라면 built in command를 실행하도록 하고 
        아니라면 execute file의 path로 인식을 하여 해당 파일을 실행하도록 하는 프로그램입니다. 
    이 프로그램에는 파일 실행 방법이 bg와 fg가 있는데 
        bg는 background에서 프로그램을 실행하도록 하여 기다림 없이 다음 명령어를 처리하도록 한 방법이고
        fg는 foreground에서 프로그램을 실행하도록 하여 다음 명령어 처리를 foreground프로그램이 끝날 때까지 기다리도록 하는 실행 방법입니다.
    보통적으로 fg방법으로 실행하도록 하게 하고 명령어에 &가 있다면 background에서 실행하도록 하여야 합니다. 

    비어있는 펑션
        eval                eval펑션은 명령을 입력 받아서 built in command평션으로 처리를 하거나 혹은 fork로 
                            프로세스를 만들어서 파일을 execve펑션으로 실행하도록 함
        Built in command    Built in command에서 처리해야 할 명령에는 jobs, bg, fg, quit 4가지가있습니다. 
            jobs            jobs: background작업을 리스팅
            quit            프로그램종료
            bg <job>:       해당 job 프로세스를 bg로 실행하도록 바꿈
            fg <job>:       해당 job 프로세스를 fg로 실행하도록 바꿈
        Waitfg              Waitfg는 fg실행시에 행하는 wait작업입니다

    
    
    
    
    리포트는 작업하신 각각의 펑션들에 대하여 동작을 설명하시면 됩니다. 정해진 형식은 없으며 장수만 1-2장으로 2장 넘어가지 
    않게 작성 해주시면 됩니다. 
    
    
    
    총점수는 코드 90점 리포트 10점입니다. 코드점수는 각각의 주어진 테스트 케이스 1개당 같은 결과를 출력하면 9점이 주어집니다.
    
    
    

    
	코드는 Gitlab에 2019/11/30 11:59PM 까지 올려주시기 바립니다.
	(gitLab에 업로드가 가능한지 미리 확인 부탁드립니다.)
	코드를 올릴때는 assignment3/tsh.c 형태로 업로드 하시면 됩니다. (다른 기타 코드 파일들도 포함)
    리포트도 올릴떄는 assignment3/학번.pdf (ex assignment3/2002209202.pdf) 형태로 업로드해주시길 바랍니다
	tsh.c 코드는 make testXX(ex make test01)가 에러없이 정상적으로 돌아가는것을 확인한후 제출하셔야 합니다. 
	제출이 이와 다를시 점수에 불이익이 있을수 있습니다.
	
	24시간까지 늦게 제출하는 경우에 50% 감점이며 24시간 이후 제출은 0점입니다.
    
    
2. 과제 수행 및 테스트 방법

	2.1 shlab-handout 디렉터리로 이동
	2.2 tsh.c 파일을 에디터로 오픈 
	2.3 수정 후 저장
    2.4 make입력으로 make처리
	2.5 make test01로 trace01.txt 테스트 케이스 01를 우리가 구현한 프로그램으로 실행
    2.6 make rtest01로 trace01.txt 테스트 케이스 01를 정답 프로그램으로 주어진 프로그램으로 실행
    2.7 2.5 2.6의 결과를 비교하여 같은 결과로 정상적으로 처리되었는지 확인
    2.8 위의 2.5 2.6 2.7작업을 test01에서 testXX(ex test02)로 값을 바꾸어서 10개의 테스트 케이스 결과 확인
    
    
    재대로 구현하였는지를 확인하기위해 
    컴파일된 정답 쉘프로그래램이 제공되어고 해당 프로그램과 같은 동작을 확인하여 점수가 매겨지게됩니다(혹은 tshref.out 결과와 같거나)
    테스트 케이스10개 trace01.txt - trace10.txt가 주어지고 
        make test01로 우리가 구현한 프로그래밍의 결과를 확인하고
        make test01로 정답 결과를 확인하여 비교하시면됩니다
    같은 결과를 출력하여야하고 다른 형태로 출력시 점수에 불이익이 있을수있습니다
        
    
    
	
    
3. sdriver.pl 실행 시 에러가 발생하는 경우 
	3.1 라이브러리 설치
		sudo apt-get install g++-multilib
		sudo apt-get install make

		위의 패키지 설치후 에러가 발생 시 
			sudo apt-get update
			sudo apt-get upgrade
			sudo apt-get install g++-multilib
			sudo apt-get install make

	3.2 권한 설정
		shlab-handout 디렉터리로 이동후
		chmod +x *
	
4. 기타 사항
	다른 문의 사항이 있으신경우 92hyungjun@gmail.com 로 연락 부탁드립니다.
	
    과제에 대한 자세한 내용은 sp_assignment3.pdf파일을 참조하세요.


